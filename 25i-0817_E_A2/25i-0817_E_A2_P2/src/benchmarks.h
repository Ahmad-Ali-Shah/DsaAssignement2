#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#include "stack.h"
#include "circularQueue.h"

using namespace std;

class BenchmarkRunner {
private:
    static double measureSinglePush(const int* data, int n) {
        stackType<int> s(n);
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            s.push(data[i]);
        }
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::micro>(endTime - startTime).count();
    }

    static double measureBatchPush(const int* data, int n) {
        stackType<int> s(n);
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        s.pushBatch(data, n);
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::micro>(endTime - startTime).count();
    }

    static double measureSingleQueue(const int* data, int n) {
        queueType<int> q(n);
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            q.addQueue(data[i]);
        }
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::micro>(endTime - startTime).count();
    }

    static double measureBatchQueue(const int* data, int n) {
        queueType<int> q(n);
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        q.addQueueBatch(data, n);
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::micro>(endTime - startTime).count();
    }

public:
    static void runBatchBenchmarks() {
        cout << "\n=========================================================================\n";
        cout << "          SECTION 7.4 & 7.5: SINGLE VS BATCHED OPERATIONS BENCHMARK      \n";
        cout << "=========================================================================\n";

        int testSizes[] = {1000, 10000, 100000};

        cout << std::left << std::setw(12) << "Item Count"
                  << std::setw(18) << "Single Push (us)"
                  << std::setw(18) << "Batch Push (us)"
                  << std::setw(18) << "Single AddQ (us)"
                  << std::setw(18) << "Batch AddQ (us)"
                  << "Speedup\n";
        cout << "-----------------------------------------------------------------------------------------\n";

        for (int n : testSizes) {
            int* data = new int[n];
            for (int i = 0; i < n; i++) {
                data[i] = 42;
            }

            double singlePushUs = measureSinglePush(data, n);
            double batchPushUs  = measureBatchPush(data, n);
            double singleQUs    = measureSingleQueue(data, n);
            double batchQUs     = measureBatchQueue(data, n);

            delete[] data;

            double pushSpeedup = singlePushUs / (batchPushUs > 0.001 ? batchPushUs : 0.001);

            cout << std::left << std::setw(12) << n
                      << std::setw(18) << std::fixed << std::setprecision(1) << singlePushUs
                      << std::setw(18) << batchPushUs
                      << std::setw(18) << singleQUs
                      << std::setw(18) << batchQUs
                      << std::fixed << std::setprecision(2) << pushSpeedup << "x\n";
        }

        cout << "=========================================================================================\n\n";
    }
};
