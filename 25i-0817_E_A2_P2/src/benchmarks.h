#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#include "stack.h"
#include "circularQueue.h"

class BenchmarkRunner {
public:
    static void runBatchBenchmarks() {
        std::cout << "\n=========================================================================\n";
        std::cout << "          SECTION 7.4 & 7.5: SINGLE VS BATCHED OPERATIONS BENCHMARK      \n";
        std::cout << "=========================================================================\n";

        int testSizes[] = {1000, 10000, 100000};

        std::cout << std::left << std::setw(12) << "Item Count"
                  << std::setw(18) << "Single Push (us)"
                  << std::setw(18) << "Batch Push (us)"
                  << std::setw(18) << "Single AddQ (us)"
                  << std::setw(18) << "Batch AddQ (us)"
                  << "Speedup\n";
        std::cout << "-----------------------------------------------------------------------------------------\n";

        for (int N : testSizes) {
            int* data = new int[N];
            for (int i = 0; i < N; i++) data[i] = 42;

            typedef std::chrono::high_resolution_clock::time_point TimePoint;

            // 1. Stack Single Push
            TimePoint t0 = std::chrono::high_resolution_clock::now();
            stackType<int> s1(N);
            for (int i = 0; i < N; i++) s1.push(data[i]);
            TimePoint t1 = std::chrono::high_resolution_clock::now();
            double singlePushUs = std::chrono::duration<double, std::micro>(t1 - t0).count();

            // 2. Stack Batch Push
            TimePoint t2 = std::chrono::high_resolution_clock::now();
            stackType<int> s2(N);
            s2.pushBatch(data, N);
            TimePoint t3 = std::chrono::high_resolution_clock::now();
            double batchPushUs = std::chrono::duration<double, std::micro>(t3 - t2).count();

            // 3. Queue Single Enqueue
            TimePoint t4 = std::chrono::high_resolution_clock::now();
            queueType<int> q1(N);
            for (int i = 0; i < N; i++) q1.addQueue(data[i]);
            TimePoint t5 = std::chrono::high_resolution_clock::now();
            double singleQUs = std::chrono::duration<double, std::micro>(t5 - t4).count();

            // 4. Queue Batch Enqueue
            TimePoint t6 = std::chrono::high_resolution_clock::now();
            queueType<int> q2(N);
            q2.addQueueBatch(data, N);
            TimePoint t7 = std::chrono::high_resolution_clock::now();
            double batchQUs = std::chrono::duration<double, std::micro>(t7 - t6).count();

            delete[] data;

            double pushSpeedup = singlePushUs / (batchPushUs > 0.001 ? batchPushUs : 0.001);

            std::cout << std::left << std::setw(12) << N
                      << std::setw(18) << std::fixed << std::setprecision(1) << singlePushUs
                      << std::setw(18) << batchPushUs
                      << std::setw(18) << singleQUs
                      << std::setw(18) << batchQUs
                      << std::fixed << std::setprecision(2) << pushSpeedup << "x\n";
        }

        std::cout << "=========================================================================================\n\n";
    }
};
