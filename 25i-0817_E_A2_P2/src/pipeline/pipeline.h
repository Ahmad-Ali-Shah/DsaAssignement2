#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "../circularQueue.h"
#include "../priorityQueue.h"
#include "../history/history.h"
#include "../coreImageFunctions/resize.h"
#include "../coreImageFunctions/blur.h"
#include "../coreImageFunctions/bucketFillStructBased.h"
#include "../coreImageFunctions/bucketFillQueueBased.h"
#include "../read/write.h"
#include "job.h"

#include "workloadBenchmark.h"

class ProcessingPipeline {

private:

    int mode; 
    queueType<Job> fifoQueue;

    priorityQueueType<Job> prioQueue;
    
    int nextJobId;

    int addCount;

    int deleteCount;

    int maxRecordedQueueSize;

    long long globalArrivalSeq;


public:
    ProcessingPipeline(int queueCapacity = 100, int m = SchedulerMode::PRIORITY): mode(m), fifoQueue(queueCapacity), prioQueue(queueCapacity), nextJobId(1), addCount(0), deleteCount(0), maxRecordedQueueSize(0), globalArrivalSeq(0) {}

    void setMode(int m) {
        mode = m;
        std::cout << "[Pipeline] Scheduler mode set to: " << (mode == SchedulerMode::FIFO ? "FIFO (Phase 1)" : "PRIORITY (Phase 2)") << "\n";
    }

    int getMode() const {
         return mode;
         }

    bool addJob(Job job) {

        job.id = nextJobId++;

        job.arrivalTime = ++globalArrivalSeq;


        if (mode == SchedulerMode::FIFO) {

            if (fifoQueue.isFullQueue()) {

                std::cout << "[Pipeline Full] Cannot add job: " << job.name << "\n";

                return false;

            }

            fifoQueue.addQueue(job);

            if (fifoQueue.size() > maxRecordedQueueSize)
             maxRecordedQueueSize = fifoQueue.size();
            
        } 
        else {

            if (prioQueue.isFullQueue()) {
                
                std::cout << "[Pipeline Full] Cannot add job: " << job.name << "\n";

                return false;

            }

            prioQueue.addQueue(job);

            if (prioQueue.size() > maxRecordedQueueSize)
             maxRecordedQueueSize = prioQueue.size();

        }

        addCount++;


        std::cout << "[Pipeline] Added Job #" << job.id << " [" << job.name  << " | Pri: " << job.priority << " | Seq: " << job.arrivalTime << "]\n";

        return true;

    }

    int getCurrentQueueSize() const {

        return (mode == SchedulerMode::FIFO) ? fifoQueue.size() : prioQueue.size();

    }

    int size() const { 
        return getCurrentQueueSize(); 
    }
    void clearQueue() {
         clearJobs(); 
        }

    Job peekNextJob() const {

        if (isEmpty()) 
        return Job();

        return (mode == SchedulerMode::FIFO) ? fifoQueue.front() : prioQueue.front();

    }

    bool isEmpty() const {

        return (mode == SchedulerMode::FIFO) ? fifoQueue.isEmptyQueue() : prioQueue.isEmptyQueue();

    }

    void listPendingJobs() const {

        if (isEmpty()) {

            std::cout << "[Pipeline] No pending jobs.\n";

            return;

        }

        std::cout << "\n--- Pending Jobs (" << (mode == SchedulerMode::FIFO ? "FIFO" : "PRIORITY") << ") ---\n";

        int sz = getCurrentQueueSize();

        for (int i = 0; i < sz; i++) {

            Job j = (mode == SchedulerMode::FIFO) ? fifoQueue.getAt(i) : prioQueue.getAt(i);


            std::cout << "  [" << (i + 1) << "] Job #" << j.id << ": " << j.name << " (Priority: " << j.priority << ", Arr: " << j.arrivalTime << ")";

            if (j.isBarrier()) 
            std::cout << " [BARRIER]";

            if (j.isCancelled) 
            std::cout << " (CANCELLED)";

            std::cout << "\n";
        }

        std::cout << "------------------------------------\n";
        
    }

    int getPendingJobs(Job out[], int maxCount) const {
        int sz = getCurrentQueueSize();
        int cnt = (sz < maxCount) ? sz : maxCount;
        for (int i = 0; i < cnt; i++) {
            out[i] = (mode == SchedulerMode::FIFO) ? fifoQueue.getAt(i) : prioQueue.getAt(i);
        }
        return cnt;
    }

    void clearJobs() {
        if (mode == SchedulerMode::FIFO) {
            while (!fifoQueue.isEmptyQueue()) { fifoQueue.deleteQueue(); deleteCount++; }
        } else {
            while (!prioQueue.isEmptyQueue()) { prioQueue.deleteQueue(); deleteCount++; }
        }
        std::cout << "[Pipeline] All pending jobs cleared.\n";
    }

    bool processNextJob(Pixel**& img, int& w, int& h, HistoryManager& history) {
        if (isEmpty()) {
            std::cout << "[Pipeline] No pending jobs to process.\n";
            return false;
        }

        Job currentJob;
        if (mode == SchedulerMode::FIFO) {
            currentJob = fifoQueue.front();
            fifoQueue.deleteQueue();
        } else {
            currentJob = prioQueue.front();
            prioQueue.deleteQueue();
        }
        deleteCount++;

        if (currentJob.isCancelled) {
            std::cout << "[Pipeline] Skipping cancelled Job #" << currentJob.id << ": " << currentJob.name << "\n";
            return true;
        }

        std::cout << "[Pipeline] Executing Job #" << currentJob.id << " [" << currentJob.name
                  << " | Pri: " << currentJob.priority << "]...\n";

        switch (currentJob.type) {
            case JobType::UNDO_REDO:
                if (currentJob.name.find("Undo") != std::string::npos) {
                    history.undo(img, w, h);
                } else {
                    history.redo(img, w, h);
                }
                break;
            case JobType::RESIZE:
                history.recordGridOperation(currentJob.name, HistoryOpType::RESIZE, img, w, h);
                img = scaling::applyResize(img, w, h, currentJob.targetW, currentJob.targetH);
                break;
            case JobType::BLUR:
                history.recordGridOperation(currentJob.name, HistoryOpType::BLUR, img, w, h);
                FrobeniusMatrixInnerProductForBlurr::applyBlur(img, w, h);
                break;
            case JobType::BUCKET_FILL_STACK: {
                if (img && w > 0 && h > 0 && currentJob.startX >= 0 && currentJob.startX < w && currentJob.startY >= 0 && currentJob.startY < h) {
                    Pixel orig = img[currentJob.startY][currentJob.startX];
                    Pixel target{currentJob.r, currentJob.g, currentJob.b};
                    Point* changed = new Point[w * h];
                    int changedCount = 0;
                    MybucketFill::ReplaceNearOne(img, w, h, currentJob.startX, currentJob.startY, currentJob.r, currentJob.g, currentJob.b);
                    for (int y = 0; y < h; y++) {
                        for (int x = 0; x < w; x++) {
                            if (img[y][x] == target) {
                                changed[changedCount++] = {x, y};
                            }
                        }
                    }
                    history.recordBucketFill(orig, target, changed, changedCount, w, h);
                    delete[] changed;
                }
                break;
            }
            case JobType::BUCKET_FILL_QUEUE: {
                if (img && w > 0 && h > 0 && currentJob.startX >= 0 && currentJob.startX < w && currentJob.startY >= 0 && currentJob.startY < h) {
                    Pixel orig = img[currentJob.startY][currentJob.startX];
                    Pixel target{currentJob.r, currentJob.g, currentJob.b};
                    Point* changed = new Point[w * h];
                    int changedCount = 0;
                    MybucketFill::ReplaceNearOneQueue(img, w, h, currentJob.startX, currentJob.startY, currentJob.r, currentJob.g, currentJob.b);
                    for (int y = 0; y < h; y++) {
                        for (int x = 0; x < w; x++) {
                            if (img[y][x] == target) {
                                changed[changedCount++] = {x, y};
                            }
                        }
                    }
                    history.recordBucketFill(orig, target, changed, changedCount, w, h);
                    delete[] changed;
                }
                break;
            }
            case JobType::SAVE_PROJECT:
            case JobType::EXPORT_IMAGE:
                ReadPath::Write(currentJob.filePath, img, w, h, true);
                std::cout << "[Pipeline Barrier] Image written to: " << currentJob.filePath << "\n";
                break;
        }

        std::cout << "[Pipeline] Job #" << currentJob.id << " finished successfully!\n";
        return true;
    }

    void processAllJobs(Pixel**& img, int& w, int& h, HistoryManager& history) {
        while (!isEmpty()) {
            processNextJob(img, w, h, history);
        }
    }

    // --- Section 7.3: Workload Comparison (delegated to workloadBenchmark.h) ---
    static void generateStandard30JobWorkload(Job outWorkload[]) {
        WorkloadBenchmark::generateStandard30JobWorkload(outWorkload);
    }

    static ExecutionStats simulateWorkload(const Job originalJobs[], int totalJobs, int runMode) {
        return WorkloadBenchmark::simulateWorkload(originalJobs, totalJobs, runMode);
    }

    static void runBenchmarkComparison() {
        WorkloadBenchmark::runBenchmarkComparison();
    }
};
