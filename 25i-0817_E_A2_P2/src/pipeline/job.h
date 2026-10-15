#pragma once
#include <string>


namespace JobType {
    // GIVING ACH ONE AS PROPER INDEX AS ENUM IS PROHIBITED

    const int UNDO_REDO = 1;

    const int BLUR = 2;

    const int BUCKET_FILL_STACK = 3;

    const int BUCKET_FILL_QUEUE = 4;

    const int RESIZE = 5;

    const int SAVE_PROJECT = 6;

    const int EXPORT_IMAGE = 7;

}

struct Job {
    int id;
    int type;               
    std::string name;
    bool isCancelled;
    int priority;           // 1 = Undo/Redo, 2 = Blur/Bucket, 3 = Resize, 4 = Save/Export
    long long arrivalTime;  // Sequence number or submission timestamp
    double estimatedCost;   // Estimated execution cost / time

    // Parameters
    int targetW, targetH;

    int startX, startY;

    unsigned int r, g, b;

    std::string filePath;


    static int defaultPriorityForType(int t) {

        if (t == JobType::UNDO_REDO) // UNDO OPERATION AND REDO
        return 1;
        if (t == JobType::BLUR || t == JobType::BUCKET_FILL_STACK || t == JobType::BUCKET_FILL_QUEUE)  // OPERATIONS 
        return 2;
        if (t == JobType::RESIZE) // RESIZING 
        return 3;
        if (t == JobType::SAVE_PROJECT || t == JobType::EXPORT_IMAGE)//STORE AND EXPORT  
        return 4;

        return 3;
    }

    bool isBarrier() const {

        return priority == 4;

    }

    Job() : id(0), type(JobType::BLUR), name(""), isCancelled(false), priority(2), arrivalTime(0), estimatedCost(1.0),targetW(0), targetH(0), startX(0), startY(0), r(0), g(0), b(0), filePath("") 
    {
        // DEFAULT CONSTRUCTOR 
    }

    Job(int jobId, int jType, const std::string& jName, int p = -1, long long arr = 0, double cost = 1.0): id(jobId), type(jType), name(jName), isCancelled(false),arrivalTime(arr), estimatedCost(cost), targetW(0), targetH(0), startX(0), startY(0), r(0), g(0), b(0), filePath("")
    {

        priority = (p > 0) ? p : defaultPriorityForType(jType);

    }
};
