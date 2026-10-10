#pragma once
#include <iostream>
#include <string>
#include "../CircularQueue.h"
#include "../history/history.h"
#include "../coreImageFunctions/resize.h"
#include "../coreImageFunctions/blur.h"
#include "../coreImageFunctions/bucketFill_StructBased.h"
#include "../coreImageFunctions/bucketFill_QueueBased.h"
#include "../read/write.h"
#include "job.h"

class ProcessingPipeline {
private:
    queueType<Job> jobQueue;
    int nextJobId;
    int addCount;
    int deleteCount;
    int maxRecordedQueueSize;

public:
    ProcessingPipeline(int queueCapacity = 20)
        : jobQueue(queueCapacity), nextJobId(1), addCount(0), deleteCount(0), maxRecordedQueueSize(0) {}

    bool addJob(Job job) {
        if (jobQueue.isFullQueue()) {
            std::cout << "[Pipeline Full] Cannot add job: " << job.name << ". Please process pending jobs first.\n";
            return false;
        }
        job.id = nextJobId++;
        jobQueue.addQueue(job);
        addCount++;
        if (jobQueue.size() > maxRecordedQueueSize) {
            maxRecordedQueueSize = jobQueue.size();
        }
        std::cout << "[Pipeline] Added Job #" << job.id << ": " << job.name << "\n";
        return true;
    }

    void listPendingJobs() const {
        if (jobQueue.isEmptyQueue()) {
            std::cout << "[Pipeline] No pending jobs.\n";
            return;
        }
        std::cout << "\n--- Pending Jobs (FRONT to REAR) ---\n";
        for (int i = 0; i < jobQueue.size(); i++) {
            Job j = jobQueue.getAt(i);
            std::cout << "  [" << (i + 1) << "] Job #" << j.id << ": " << j.name;
            if (j.isCancelled) {
                std::cout << " (CANCELLED)";
            }
            std::cout << "\n";
        }
        std::cout << "------------------------------------\n";
    }

    bool cancelJob(int jobId) {
        for (int i = 0; i < jobQueue.size(); i++) {
            Job j = jobQueue.getAt(i);
            if (j.id == jobId) {
                if (j.isCancelled) {
                    std::cout << "[Pipeline] Job #" << jobId << " is already cancelled.\n";
                    return true;
                }
                // Update in place by reassigning logical element or marking
                // CircularQueue doesn't have mutable ref, so we re-drain if needed or mark cancelled
                // Let's create a temporary queue to flip cancelled flag without shifting:
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
                std::cout << "[Pipeline] Successfully marked Job #" << jobId << " as cancelled.\n";
                return true;
            }
        }
        std::cout << "[Pipeline] Job #" << jobId << " not found in queue.\n";
        return false;
    }

    void clearJobs() {
        while (!jobQueue.isEmptyQueue()) {
            jobQueue.deleteQueue();
            deleteCount++;
        }
        std::cout << "[Pipeline] All pending jobs cleared.\n";
    }

    bool processNextJob(Pixel**& img, int& w, int& h, HistoryManager& history) {
        if (jobQueue.isEmptyQueue()) {
            std::cout << "[Pipeline] No pending jobs to process.\n";
            return false;
        }

        Job currentJob = jobQueue.front();
        jobQueue.deleteQueue();
        deleteCount++;

        if (currentJob.isCancelled) {
            std::cout << "[Pipeline] Skipping cancelled Job #" << currentJob.id << ": " << currentJob.name << "\n";
            return true;
        }

        std::cout << "[Pipeline] Executing Job #" << currentJob.id << ": " << currentJob.name << "...\n";

        // Snapshot before executing so it can be recorded into Undo history
        history.recordAction(currentJob.name, img, w, h);

        switch (currentJob.type) {
            case JobType::RESIZE:
                img = scaling::applyResize(img, w, h, currentJob.targetW, currentJob.targetH);
                break;
            case JobType::BLUR:
                FrobeniusMatrixInnerProductForBlurr::applyBlur(img, w, h);
                break;
            case JobType::BUCKET_FILL_STACK:
                MybucketFill::ReplaceNearOne(img, w, h, currentJob.startX, currentJob.startY, currentJob.r, currentJob.g, currentJob.b);
                break;
            case JobType::BUCKET_FILL_QUEUE:
                MybucketFill::ReplaceNearOneQueue(img, w, h, currentJob.startX, currentJob.startY, currentJob.r, currentJob.g, currentJob.b);
                break;
            case JobType::SAVE_PROJECT:
            case JobType::EXPORT_IMAGE:
                ReadPath::Write(currentJob.filePath, img, w, h, true);
                std::cout << "[Pipeline] Image written to: " << currentJob.filePath << "\n";
                break;
        }

        std::cout << "[Pipeline] Job #" << currentJob.id << " finished successfully!\n";
        return true;
    }

    void processAllJobs(Pixel**& img, int& w, int& h, HistoryManager& history) {
        if (jobQueue.isEmptyQueue()) {
            std::cout << "[Pipeline] No pending jobs to process.\n";
            return;
        }
        while (!jobQueue.isEmptyQueue()) {
            processNextJob(img, w, h, history);
        }
    }

    int size() const { return jobQueue.size(); }
    int capacity() const { return jobQueue.capacity(); }
    void clearQueue() { clearJobs(); }

    int getPendingJobs(Job out[], int maxCount) const {
        int cnt = jobQueue.size() < maxCount ? jobQueue.size() : maxCount;
        for (int i = 0; i < cnt; i++) {
            out[i] = jobQueue.getAt(i);
        }
        return cnt;
    }

    int getCurrentQueueSize() const { return jobQueue.size(); }
    int getMaxRecordedQueueSize() const { return maxRecordedQueueSize; }
    int getAddCount() const { return addCount; }
    int getDeleteCount() const { return deleteCount; }
    bool isEmpty() const { return jobQueue.isEmptyQueue(); }

    void printPendingJobNames() const {
        if (jobQueue.isEmptyQueue()) {
            std::cout << "[Empty]\n";
            return;
        }
        for (int i = 0; i < jobQueue.size(); i++) {
            Job j = jobQueue.getAt(i);
            std::cout << j.name;
            if (j.isCancelled) std::cout << "(C)";
            std::cout << " ";
        }
        std::cout << "\n";
    }
};
