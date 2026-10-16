#pragma once
#include <iostream>
#include <string>

#include "pipeline/job.h"

using namespace std;

// overloaded function to find out the priorities

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

    return item.isBarrier();// functiionality of job 

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

    /////////////////////////////

    // constructor 

    ////////////////////////////


    priorityQueueType(int queueSize = 100) {
       
        if (queueSize <= 0) 
        queueSize = 100;

        maxSize = queueSize;

        count = 0;

        array = new Type[maxSize];

    }

    /////////////////////////////////////////


    // Destructor 

    //////////////////////////////



    ~priorityQueueType() {

        delete[] array;

        array = nullptr;

    }


    ///////////////////////////////


    // copy constructor 

    ////////////////////////


    priorityQueueType(const priorityQueueType<Type>& other) {

        maxSize = other.maxSize;

        count = other.count;

        array = new Type[maxSize];

        for (int i = 0; i < count; i++) {

            array[i] = other.array[i];

        }

    }

    ///////////////////////////////////////////

    // Equal Opeator 


    ///////////////////////////////////



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

        if (index < 0 || index >= count) 
        return Type();

        return array[index];

    }

    ///////////////////////////////////////

    // I chose unordered queue 

    /////////////////////////////
    
    //
    void addQueue(const Type& item) {

        if (isFullQueue()) {

            // just resize as you mentioned that it can be dynamic 

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

    // for deleteto helping to find best index having same value 

    int findBestIndex() const {

        if (count == 0) 
        return -1;

        
        int firstBarrierIdx = -1;

        for (int i = 0; i < count; i++) {

            if (itemBarrier(array[i])) {

                firstBarrierIdx = i;

                break;

            }// since we need to remove the barieer aas mentioned in phase 2 

        }

        // edge case if at first 

        if (firstBarrierIdx == 0) {
            return 0;
        }

    
        int limit = (firstBarrierIdx > 0) ? firstBarrierIdx : count; // iif head then whole array else start 

        int bestIdx = 0;

        for (int i = 1; i < limit; i++) {

            int pI = itemPriority(array[i]);

            int pBest = itemPriority(array[bestIdx]);

            if (pI < pBest) {

                bestIdx = i;

            } 
            else if (pI == pBest) {

              
                if (itemArrival(array[i]) < itemArrival(array[bestIdx])) {

                    bestIdx = i;

                }

            }

        }

        return bestIdx;

    }

    Type front() const {

        if (isEmptyQueue()) {

            cout << "[Empty Queue]\n";

            return Type();

        }
        int bestIdx = findBestIndex(); // front always return the max value or the best value 

        return array[bestIdx];


    }

    void deleteQueue() {


        if (isEmptyQueue()) {

            cout << "[Already Deleted]\n";

            return;

        }

        int bestIdx = findBestIndex();

        for (int i = bestIdx + 1; i < count; i++) {

            array[i - 1] = array[i];

        }

        count--;
        // just swap next with prev 

    }

    void print() const {

        if (isEmptyQueue()) {

            cout << "[Empty Queue]\n";

            return;

        }


        for (int i = 0; i < count; i++) {

            cout << "[Job Pri: " << itemPriority(array[i]) << "] ";

        }

        cout << "\n";

    }
    
};
