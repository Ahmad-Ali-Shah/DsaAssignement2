#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "../CircularQueue.h"
#include "../priorityQueue.h"
#include "../history/history.h"
#include "../coreImageFunctions/resize.h"
#include "../coreImageFunctions/blur.h"
#include "../coreImageFunctions/bucketFill_StructBased.h"
#include "../coreImageFunctions/bucketFill_QueueBased.h"
#include "../read/write.h"
#include "job.h"

// Scheduler Mode constants (no enum)
namespace SchedulerMode {
    const int FIFO = 0;
    const int PRIORITY = 1;
}

struct ExecutionStats {
    int totalJobs;
    double avgWaitTime;
    double avgCompletionTime;
    double avgP1WaitTime;
};

class ProcessingPipeline {
private:
    int mode; // SchedulerMode::FIFO or PRIORITY
    queueType<Job> fifoQueue;
    priorityQueueType<Job> prioQueue;
    int nextJobId;
    int addCount;
    int deleteCount;
    int maxRecordedQueueSize;
    long long globalArrivalSeq;

public:
    ProcessingPipeline(int queueCapacity = 100, int m = SchedulerMode::PRIORITY)
        : mode(m), fifoQueue(queueCapacity), prioQueue(queueCapacity),
          nextJobId(1), addCount(0), deleteCount(0), maxRecordedQueueSize(0), globalArrivalSeq(0) {}

    void setMode(int m) {
        mode = m;
        std::cout << "[Pipeline] Scheduler mode set to: "
                  << (mode == SchedulerMode::FIFO ? "FIFO (Phase 1)" : "PRIORITY (Phase 2)") << "\n";
    }

    int getMode() const { return mode; }

    bool addJob(Job job) {
        job.id = nextJobId++;
        job.arrivalTime = ++globalArrivalSeq;

        if (mode == SchedulerMode::FIFO) {
            if (fifoQueue.isFullQueue()) {
                std::cout << "[Pipeline Full] Cannot add job: " << job.name << "\n";
                return false;
            }
            fifoQueue.addQueue(job);
            if (fifoQueue.size() > maxRecordedQueueSize) maxRecordedQueueSize = fifoQueue.size();
        } else {
            if (prioQueue.isFullQueue()) {
                std::cout << "[Pipeline Full] Cannot add job: " << job.name << "\n";
                return false;
            }
            prioQueue.addQueue(job);
            if (prioQueue.size() > maxRecordedQueueSize) maxRecordedQueueSize = prioQueue.size();
        }

        addCount++;
        std::cout << "[Pipeline] Added Job #" << job.id << " [" << job.name
                  << " | Pri: " << job.priority << " | Seq: " << job.arrivalTime << "]\n";
        return true;
    }

    int getCurrentQueueSize() const {
        return (mode == SchedulerMode::FIFO) ? fifoQueue.size() : prioQueue.size();
    }

    int size() const { return getCurrentQueueSize(); }
    void clearQueue() { clearJobs(); }

    Job peekNextJob() const {
        if (isEmpty()) return Job();
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
            std::cout << "  [" << (i + 1) << "] Job #" << j.id << ": " << j.name
                      << " (Priority: " << j.priority << ", Arr: " << j.arrivalTime << ")";
            if (j.isBarrier()) std::cout << " [BARRIER]";
            if (j.isCancelled) std::cout << " (CANCELLED)";
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

    // --- Section 7.3: Workload Comparison (30 Jobs FIFO vs Priority) without STL ---
    static void generateStandard30JobWorkload(Job outWorkload[]) {
        int id = 1;
        long long arr = 1;

        // Group 1: 10 jobs before first barrier
        outWorkload[0] = Job(id++, JobType::RESIZE, "Resize 1", 3, arr++, 60.0);
        outWorkload[1] = Job(id++, JobType::BLUR, "Blur 1", 2, arr++, 40.0);
        outWorkload[2] = Job(id++, JobType::BUCKET_FILL_STACK, "BucketFill 1", 2, arr++, 25.0);
        outWorkload[3] = Job(id++, JobType::UNDO_REDO, "Undo Request 1", 1, arr++, 5.0);
        outWorkload[4] = Job(id++, JobType::RESIZE, "Resize 2", 3, arr++, 60.0);
        outWorkload[5] = Job(id++, JobType::BLUR, "Blur 2", 2, arr++, 40.0);
        outWorkload[6] = Job(id++, JobType::UNDO_REDO, "Redo Request 1", 1, arr++, 5.0);
        outWorkload[7] = Job(id++, JobType::BUCKET_FILL_QUEUE, "BucketFill 2", 2, arr++, 25.0);
        outWorkload[8] = Job(id++, JobType::RESIZE, "Resize 3", 3, arr++, 60.0);
        outWorkload[9] = Job(id++, JobType::EXPORT_IMAGE, "Export Snapshot 1", 4, arr++, 100.0); // Barrier 1

        // Group 2: 10 jobs between Barrier 1 and Barrier 2
        outWorkload[10] = Job(id++, JobType::RESIZE, "Resize 4", 3, arr++, 60.0);
        outWorkload[11] = Job(id++, JobType::UNDO_REDO, "Undo Request 2", 1, arr++, 5.0);
        outWorkload[12] = Job(id++, JobType::BLUR, "Blur 3", 2, arr++, 40.0);
        outWorkload[13] = Job(id++, JobType::BUCKET_FILL_STACK, "BucketFill 3", 2, arr++, 25.0);
        outWorkload[14] = Job(id++, JobType::BLUR, "Blur 4", 2, arr++, 40.0);
        outWorkload[15] = Job(id++, JobType::UNDO_REDO, "Undo Request 3", 1, arr++, 5.0);
        outWorkload[16] = Job(id++, JobType::RESIZE, "Resize 5", 3, arr++, 60.0);
        outWorkload[17] = Job(id++, JobType::BUCKET_FILL_QUEUE, "BucketFill 4", 2, arr++, 25.0);
        outWorkload[18] = Job(id++, JobType::BLUR, "Blur 5", 2, arr++, 40.0);
        outWorkload[19] = Job(id++, JobType::SAVE_PROJECT, "Save Project 1", 4, arr++, 100.0); // Barrier 2

        // Group 3: 10 jobs after Barrier 2
        outWorkload[20] = Job(id++, JobType::RESIZE, "Resize 6", 3, arr++, 60.0);
        outWorkload[21] = Job(id++, JobType::BLUR, "Blur 6", 2, arr++, 40.0);
        outWorkload[22] = Job(id++, JobType::UNDO_REDO, "Undo Request 4", 1, arr++, 5.0);
        outWorkload[23] = Job(id++, JobType::BUCKET_FILL_STACK, "BucketFill 5", 2, arr++, 25.0);
        outWorkload[24] = Job(id++, JobType::UNDO_REDO, "Redo Request 2", 1, arr++, 5.0);
        outWorkload[25] = Job(id++, JobType::BLUR, "Blur 7", 2, arr++, 40.0);
        outWorkload[26] = Job(id++, JobType::RESIZE, "Resize 7", 3, arr++, 60.0);
        outWorkload[27] = Job(id++, JobType::BUCKET_FILL_QUEUE, "BucketFill 6", 2, arr++, 25.0);
        outWorkload[28] = Job(id++, JobType::BLUR, "Blur 8", 2, arr++, 40.0);
        outWorkload[29] = Job(id++, JobType::EXPORT_IMAGE, "Final Export", 4, arr++, 100.0); // Final Barrier
    }

    static ExecutionStats simulateWorkload(const Job originalJobs[], int totalJobs, int runMode) {
        double currentTime = 0.0;
        double totalWait = 0.0;
        double totalCompletion = 0.0;
        double totalP1Wait = 0.0;
        int p1Count = 0;
        int totalProcessed = 0;

        if (runMode == SchedulerMode::FIFO) {
            queueType<Job> q(totalJobs + 10);
            for (int i = 0; i < totalJobs; i++) q.addQueue(originalJobs[i]);

            while (!q.isEmptyQueue()) {
                Job j = q.front();
                q.deleteQueue();

                double waitTime = currentTime;
                double compTime = currentTime + j.estimatedCost;
                currentTime = compTime;

                totalWait += waitTime;
                totalCompletion += compTime;
                if (j.priority == 1) {
                    totalP1Wait += waitTime;
                    p1Count++;
                }
                totalProcessed++;
            }
        } else {
            priorityQueueType<Job> pq(totalJobs + 10);
            for (int i = 0; i < totalJobs; i++) pq.addQueue(originalJobs[i]);

            while (!pq.isEmptyQueue()) {
                Job j = pq.front();
                pq.deleteQueue();

                double waitTime = currentTime;
                double compTime = currentTime + j.estimatedCost;
                currentTime = compTime;

                totalWait += waitTime;
                totalCompletion += compTime;
                if (j.priority == 1) {
                    totalP1Wait += waitTime;
                    p1Count++;
                }
                totalProcessed++;
            }
        }

        ExecutionStats stats;
        stats.totalJobs = totalProcessed;
        stats.avgWaitTime = totalWait / totalProcessed;
        stats.avgCompletionTime = totalCompletion / totalProcessed;
        stats.avgP1WaitTime = (p1Count > 0) ? (totalP1Wait / p1Count) : 0.0;
        return stats;
    }

    static void runBenchmarkComparison() {
        Job workload[30];
        generateStandard30JobWorkload(workload);

        std::cout << "\n=========================================================================\n";
        std::cout << "        SECTION 7.3 & 7.5: 30-JOB WORKLOAD SCHEDULER COMPARISON          \n";
        std::cout << "=========================================================================\n";

        ExecutionStats fifoStats = simulateWorkload(workload, 30, SchedulerMode::FIFO);
        ExecutionStats prioStats = simulateWorkload(workload, 30, SchedulerMode::PRIORITY);

        std::cout << std::left << std::setw(30) << "Metric"
                  << std::setw(20) << "FIFO Mode"
                  << std::setw(20) << "Priority Mode"
                  << "Improvement\n";
        std::cout << "-------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(30) << "Jobs Processed"
                  << std::setw(20) << fifoStats.totalJobs
                  << std::setw(20) << prioStats.totalJobs
                  << "Identical\n";
        std::cout << std::left << std::setw(30) << "Avg Waiting Time (ms)"
                  << std::setw(20) << std::fixed << std::setprecision(2) << fifoStats.avgWaitTime
                  << std::setw(20) << prioStats.avgWaitTime
                  << ((fifoStats.avgWaitTime - prioStats.avgWaitTime) / fifoStats.avgWaitTime * 100.0) << "%\n";
        std::cout << std::left << std::setw(30) << "Avg Completion Time (ms)"
                  << std::setw(20) << std::fixed << std::setprecision(2) << fifoStats.avgCompletionTime
                  << std::setw(20) << prioStats.avgCompletionTime
                  << ((fifoStats.avgCompletionTime - prioStats.avgCompletionTime) / fifoStats.avgCompletionTime * 100.0) << "%\n";
        std::cout << std::left << std::setw(30) << "Avg Priority-1 Wait (ms)"
                  << std::setw(20) << std::fixed << std::setprecision(2) << fifoStats.avgP1WaitTime
                  << std::setw(20) << prioStats.avgP1WaitTime
                  << "\033[1;32m" << ((fifoStats.avgP1WaitTime - prioStats.avgP1WaitTime) / fifoStats.avgP1WaitTime * 100.0) << "% faster\033[0m\n";
        std::cout << "=========================================================================\n\n";
    }
};
