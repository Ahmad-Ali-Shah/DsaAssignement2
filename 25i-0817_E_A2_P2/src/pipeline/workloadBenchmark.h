#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "../circularQueue.h"
#include "../priorityQueue.h"
#include "job.h"

using namespace std;

namespace SchedulerMode {
    const int fifo = 0;
    const int priority = 1;
}

struct ExecutionStats {
    int totalJobs;
    double avgWaitTime;
    double avgCompletionTime;
    double avgP1WaitTime;
};

class WorkloadBenchmark {
public:
    // Standard 30-job mixed priority workload (Section 7.3)
    static void generateStandard30JobWorkload(Job outWorkload[]) {
        int id = 1;
        long long arr = 1;

        // Group 1: 10 jobs before first barrier
        outWorkload[0] = Job(id++, JobType::resize, "Resize 1", 3, arr++, 60.0);
        outWorkload[1] = Job(id++, JobType::blur, "Blur 1", 2, arr++, 40.0);
        outWorkload[2] = Job(id++, JobType::bucketFillStack, "BucketFill 1", 2, arr++, 25.0);
        outWorkload[3] = Job(id++, JobType::undoRedo, "Undo Request 1", 1, arr++, 5.0);
        outWorkload[4] = Job(id++, JobType::resize, "Resize 2", 3, arr++, 60.0);
        outWorkload[5] = Job(id++, JobType::blur, "Blur 2", 2, arr++, 40.0);
        outWorkload[6] = Job(id++, JobType::undoRedo, "Redo Request 1", 1, arr++, 5.0);
        outWorkload[7] = Job(id++, JobType::bucketFillQueue, "BucketFill 2", 2, arr++, 25.0);
        outWorkload[8] = Job(id++, JobType::resize, "Resize 3", 3, arr++, 60.0);
        outWorkload[9] = Job(id++, JobType::exportImage, "Export Snapshot 1", 4, arr++, 100.0); // Barrier 1

        // Group 2: 10 jobs between Barrier 1 and Barrier 2
        outWorkload[10] = Job(id++, JobType::resize, "Resize 4", 3, arr++, 60.0);
        outWorkload[11] = Job(id++, JobType::undoRedo, "Undo Request 2", 1, arr++, 5.0);
        outWorkload[12] = Job(id++, JobType::blur, "Blur 3", 2, arr++, 40.0);
        outWorkload[13] = Job(id++, JobType::bucketFillStack, "BucketFill 3", 2, arr++, 25.0);
        outWorkload[14] = Job(id++, JobType::blur, "Blur 4", 2, arr++, 40.0);
        outWorkload[15] = Job(id++, JobType::undoRedo, "Undo Request 3", 1, arr++, 5.0);
        outWorkload[16] = Job(id++, JobType::resize, "Resize 5", 3, arr++, 60.0);
        outWorkload[17] = Job(id++, JobType::bucketFillQueue, "BucketFill 4", 2, arr++, 25.0);
        outWorkload[18] = Job(id++, JobType::blur, "Blur 5", 2, arr++, 40.0);
        outWorkload[19] = Job(id++, JobType::saveProject, "Save Project 1", 4, arr++, 100.0); // Barrier 2

        // Group 3: 10 jobs after Barrier 2
        outWorkload[20] = Job(id++, JobType::resize, "Resize 6", 3, arr++, 60.0);
        outWorkload[21] = Job(id++, JobType::blur, "Blur 6", 2, arr++, 40.0);
        outWorkload[22] = Job(id++, JobType::undoRedo, "Undo Request 4", 1, arr++, 5.0);
        outWorkload[23] = Job(id++, JobType::bucketFillStack, "BucketFill 5", 2, arr++, 25.0);
        outWorkload[24] = Job(id++, JobType::undoRedo, "Redo Request 2", 1, arr++, 5.0);
        outWorkload[25] = Job(id++, JobType::blur, "Blur 7", 2, arr++, 40.0);
        outWorkload[26] = Job(id++, JobType::resize, "Resize 7", 3, arr++, 60.0);
        outWorkload[27] = Job(id++, JobType::bucketFillQueue, "BucketFill 6", 2, arr++, 25.0);
        outWorkload[28] = Job(id++, JobType::blur, "Blur 8", 2, arr++, 40.0);
        outWorkload[29] = Job(id++, JobType::exportImage, "Final Export", 4, arr++, 100.0); // Final Barrier
    }

    static ExecutionStats simulateWorkload(const Job originalJobs[], int totalJobs, int runMode) {
        double currentTime = 0.0;
        double totalWait = 0.0;
        double totalCompletion = 0.0;
        double totalP1Wait = 0.0;
        int p1Count = 0;
        int totalProcessed = 0;

        if (runMode == SchedulerMode::fifo) {
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

        cout << "\n=========================================================================\n";
        cout << "        SECTION 7.3 & 7.5: 30-JOB WORKLOAD SCHEDULER COMPARISON          \n";
        cout << "=========================================================================\n";

        ExecutionStats fifoStats = simulateWorkload(workload, 30, SchedulerMode::fifo);
        ExecutionStats prioStats = simulateWorkload(workload, 30, SchedulerMode::priority);

        cout << std::left << std::setw(30) << "Metric"
                  << std::setw(20) << "FIFO Mode"
                  << std::setw(20) << "Priority Mode"
                  << "Improvement\n";
        cout << "-------------------------------------------------------------------------\n";
        cout << std::left << std::setw(30) << "Jobs Processed"
                  << std::setw(20) << fifoStats.totalJobs
                  << std::setw(20) << prioStats.totalJobs
                  << "Identical\n";
        cout << std::left << std::setw(30) << "Avg Waiting Time (ms)"
                  << std::setw(20) << std::fixed << std::setprecision(2) << fifoStats.avgWaitTime
                  << std::setw(20) << prioStats.avgWaitTime
                  << ((fifoStats.avgWaitTime - prioStats.avgWaitTime) / fifoStats.avgWaitTime * 100.0) << "%\n";
        cout << std::left << std::setw(30) << "Avg Completion Time (ms)"
                  << std::setw(20) << std::fixed << std::setprecision(2) << fifoStats.avgCompletionTime
                  << std::setw(20) << prioStats.avgCompletionTime
                  << ((fifoStats.avgCompletionTime - prioStats.avgCompletionTime) / fifoStats.avgCompletionTime * 100.0) << "%\n";
        cout << std::left << std::setw(30) << "Avg Priority-1 Wait (ms)"
                  << std::setw(20) << std::fixed << std::setprecision(2) << fifoStats.avgP1WaitTime
                  << std::setw(20) << prioStats.avgP1WaitTime
                  << "\033[1;32m" << ((fifoStats.avgP1WaitTime - prioStats.avgP1WaitTime) / fifoStats.avgP1WaitTime * 100.0) << "% faster\033[0m\n";
        cout << "=========================================================================\n\n";
    }
};
