#pragma once
#include <iostream>
#include <string>
#include "../circularQueue.h"
#include "../history/history.h"
#include "../coreImageFunctions/resize/applyResize.h"
#include "../coreImageFunctions/blur/applyBlur.h"
#include "../coreImageFunctions/bucketFill/bucketFillStructBased.h"
#include "../coreImageFunctions/bucketFill/bucketFillQueueBased.h"
#include "../read/write.h"
#include "job.h"

using namespace std;

class ProcessingPipeline {

private:

    queueType<Job> jobQueue;

    int nextJobId;

    int addCount;

    int deleteCount;

    int maxRecordedQueueSize;


public:

    /////////////////////////////////////////////////
    // constructor 
    ///////////////////////////////////////////////////

    ProcessingPipeline(int queueCapacity = 20) : jobQueue(queueCapacity), nextJobId(1), addCount(0), deleteCount(0), maxRecordedQueueSize(0) {}


    bool addJob(Job job) {

        if (jobQueue.isFullQueue()) {

            cout << "[Pipeline Full] Cannot add job: " << job.name << ". Please process pending jobs first.\n";

            return false;

        }

        job.id = nextJobId++;

        jobQueue.addQueue(job);

        addCount++;

        if (jobQueue.size() > maxRecordedQueueSize) {
            
            maxRecordedQueueSize = jobQueue.size();

        }

        cout << "[Pipeline] Added Job #" << job.id << ": " << job.name << "\n";


        return true;

    }

    void listPendingJobs() const {

        if (jobQueue.isEmptyQueue()) {

            cout << "[Pipeline] No pending jobs.\n";

            return;

        }

        cout << "\n--- Pending Jobs ---\n";

        for (int i = 0; i < jobQueue.size(); i++) {

            Job j = jobQueue.getAt(i);

            cout << "  [" << (i + 1) << "] Job #" << j.id << ": " << j.name;

            if (j.isCancelled) {

                cout << " (CANCELLED)";
                
            }

            cout << "\n";

        }

        cout << "------------------------------------\n";

    }

    bool cancelJob(int jobId) {

        for (int i = 0; i < jobQueue.size(); i++) {

            Job j = jobQueue.getAt(i);

            if (j.id == jobId) {

                if (j.isCancelled) {

                    cout << "[Pipeline] Job #" << jobId << " is already cancelled.\n";

                    return true;

                }

               
                queueType<Job> temp(jobQueue.capacity());

                while (!jobQueue.isEmptyQueue()) {

                    Job curr = jobQueue.front();

                    jobQueue.deleteQueue();

                    deleteCount++;

                    if (curr.id == jobId) {

                        curr.isCancelled = true;

                    }

                    temp.addQueue(curr);


                    addCount++;
                }
                while (!temp.isEmptyQueue()) {

                    jobQueue.addQueue(temp.front());

                    temp.deleteQueue();

                }

                cout << "[Pipeline] Successfully marked Job #" << jobId << " as cancelled.\n";

                return true;

            }
        }
        cout << "[Pipeline] Job #" << jobId << " not found in pending jobs.\n";

        return false;

    }

    void clearJobs() {

        while (!jobQueue.isEmptyQueue()) {

            jobQueue.deleteQueue();

            deleteCount++;

        }

        cout << "[Pipeline] All pending jobs cleared.\n";

    }

    bool processNextJob(Pixel**& img, int& w, int& h, HistoryManager& history) {

        if (jobQueue.isEmptyQueue()) {

            cout << "[Pipeline] No pending jobs to process.\n";

            return false;

        }

        Job currentJob = jobQueue.front();

        jobQueue.deleteQueue();

        deleteCount++;


        if (currentJob.isCancelled) {

            cout << "[Pipeline] Skipping cancelled Job #" << currentJob.id << ": " << currentJob.name << "\n";

            return true;

        }

        cout << "[Pipeline] Executing Job #" << currentJob.id << ": " << currentJob.name << "...\n";


        
        history.recordAction(currentJob.name, img, w, h);


        switch (currentJob.type) {

            case JobType::resize:

                img = scaling::applyResize(img, w, h, currentJob.targetW, currentJob.targetH);

                break;

            case JobType::blur:

                FrobeniusMatrixInnerProductForBlurr::applyBlur(img, w, h);

                break;
                
            case JobType::bucketFillStack:

                MybucketFill::ReplaceNearOne(img, w, h, currentJob.startX, currentJob.startY, currentJob.r, currentJob.g, currentJob.b);
                
                break;

            case JobType::bucketFillQueue:

                MybucketFill::ReplaceNearOneQueue(img, w, h, currentJob.startX, currentJob.startY, currentJob.r, currentJob.g, currentJob.b);

                break;

            case JobType::saveProject:

            case JobType::exportImage:

                ReadPath::Write(currentJob.filePath, img, w, h, true);

                cout << "[Pipeline] Image written to: " << currentJob.filePath << "\n";
                
                break;

        }

        cout << "[Pipeline] Job #" << currentJob.id << " finished successfully!\n";

        return true;

    }

    void processAllJobs(Pixel**& img, int& w, int& h, HistoryManager& history) {

        if (jobQueue.isEmptyQueue()) {

            cout << "[Pipeline] No pending jobs to process.\n";

            return;

        }

        while (!jobQueue.isEmptyQueue()) {

            processNextJob(img, w, h, history);

        }
    }

    int size() const { 
        return jobQueue.size(); 
    }
    int capacity() const { 
        return jobQueue.capacity(); 
    }
    void clearQueue() { 
        clearJobs(); 
    }

    int getPendingJobs(Job out[], int maxCount) const {

        int cnt = jobQueue.size() < maxCount ? jobQueue.size() : maxCount;

        for (int i = 0; i < cnt; i++) {

            out[i] = jobQueue.getAt(i);

        }

        return cnt;

    }

    int getCurrentQueueSize() const { 
        return jobQueue.size();
     }
    int getMaxRecordedQueueSize() const { 
        return maxRecordedQueueSize;
     }
    int getAddCount() const { 
        return addCount;
     }
    int getDeleteCount() const {
         return deleteCount;
         }
    bool isEmpty() const { 
        return jobQueue.isEmptyQueue();
     }

    void printPendingJobNames() const {

        if (jobQueue.isEmptyQueue()) {

            cout << "[Empty]\n";

            return;

        }

        for (int i = 0; i < jobQueue.size(); i++) {

            Job j = jobQueue.getAt(i);

            cout << j.name;

            if (j.isCancelled) 
            cout << "(C)";

            cout << " ";

        }

        cout << "\n";

    }
    
};
