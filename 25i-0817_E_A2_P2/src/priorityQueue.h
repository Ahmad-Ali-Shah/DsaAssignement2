#pragma once
#include <iostream>
#include <string>

#include "pipeline/job.h"

// Overloaded helper functions to extract priority, arrival, and barrier properties across types
template <typename T>
int extractJobPriority(const T& item) {
    return (int)item;
}

static int extractJobPriority(const Job& item) {
    return item.priority;
}

template <typename T>
long long extractJobArrival(const T&) {
    return 0;
}

static long long extractJobArrival(const Job& item) {
    return item.arrivalTime;
}

template <typename T>
bool extractJobBarrier(const T&) {
    return false;
}

static bool extractJobBarrier(const Job& item) {
    return item.isBarrier();
}

template <class Type>
class priorityQueueType {
private:
    Type* array;
    int maxSize;
    int count;

    int itemPriority(const Type& item) const {
        return extractJobPriority(item);
    }

    long long itemArrival(const Type& item) const {
        return extractJobArrival(item);
    }

    bool itemBarrier(const Type& item) const {
        return extractJobBarrier(item);
    }

public:
    priorityQueueType(int queueSize = 100) {
        if (queueSize <= 0) queueSize = 100;
        maxSize = queueSize;
        count = 0;
        array = new Type[maxSize];
    }

    ~priorityQueueType() {
        delete[] array;
        array = nullptr;
    }

    priorityQueueType(const priorityQueueType<Type>& other) {
        maxSize = other.maxSize;
        count = other.count;
        array = new Type[maxSize];
        for (int i = 0; i < count; i++) {
            array[i] = other.array[i];
        }
    }

    priorityQueueType<Type>& operator=(const priorityQueueType<Type>& other) {
        if (this != &other) {
            delete[] array;
            maxSize = other.maxSize;
            count = other.count;
            array = new Type[maxSize];
            for (int i = 0; i < count; i++) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    void initializeQueue() {
        count = 0;
    }

    bool isEmptyQueue() const {
        return count == 0;
    }

    bool isFullQueue() const {
        return count == maxSize;
    }

    int size() const {
        return count;
    }

    int capacity() const {
        return maxSize;
    }

    Type getAt(int index) const {
        if (index < 0 || index >= count) return Type();
        return array[index];
    }

    // Unordered Array enqueue: O(1) amortized
    void addQueue(const Type& item) {
        if (isFullQueue()) {
            int newSize = maxSize * 2;
            Type* newArray = new Type[newSize];
            for (int i = 0; i < count; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
            maxSize = newSize;
        }
        array[count++] = item;
    }

    // Finalization Barrier-aware priority selection: O(N)
    int findBestIndex() const {
        if (count == 0) return -1;

        // Step 1: Locate first barrier in queue
        int firstBarrierIdx = -1;
        for (int i = 0; i < count; i++) {
            if (itemBarrier(array[i])) {
                firstBarrierIdx = i;
                break;
            }
        }

        // If barrier is at head of queue (all preceding jobs done), run barrier
        if (firstBarrierIdx == 0) {
            return 0;
        }

        // Priority candidate search space is strictly before first barrier
        int limit = (firstBarrierIdx > 0) ? firstBarrierIdx : count;

        int bestIdx = 0;
        for (int i = 1; i < limit; i++) {
            int pI = itemPriority(array[i]);
            int pBest = itemPriority(array[bestIdx]);
            if (pI < pBest) {
                bestIdx = i;
            } else if (pI == pBest) {
                // Ties broken by earliest arrival
                if (itemArrival(array[i]) < itemArrival(array[bestIdx])) {
                    bestIdx = i;
                }
            }
        }
        return bestIdx;
    }

    Type front() const {
        if (isEmptyQueue()) {
            std::cout << "[Empty Priority Queue]\n";
            return Type();
        }
        int bestIdx = findBestIndex();
        return array[bestIdx];
    }

    void deleteQueue() {
        if (isEmptyQueue()) {
            std::cout << "[Priority Queue Underflow]\n";
            return;
        }
        int bestIdx = findBestIndex();
        for (int i = bestIdx + 1; i < count; i++) {
            array[i - 1] = array[i];
        }
        count--;
    }

    void print() const {
        if (isEmptyQueue()) {
            std::cout << "[Empty Priority Queue]\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            std::cout << "[Job Pri: " << itemPriority(array[i]) << "] ";
        }
        std::cout << "\n";
    }
};
