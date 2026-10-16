#pragma once
#include <string>


namespace JobType {
    const int undoRedo = 1;
    const int blur = 2;
    const int bucketFillStack = 3;
    const int bucketFillQueue = 4;
    const int resize = 5;
    const int saveProject = 6;
    const int exportImage = 7;
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
        if (t == JobType::undoRedo)
            return 1;
        if (t == JobType::blur || t == JobType::bucketFillStack || t == JobType::bucketFillQueue)
            return 2;
        if (t == JobType::resize)
            return 3;
        if (t == JobType::saveProject || t == JobType::exportImage)
            return 4;

        return 3;
    }

    bool isBarrier() const {
        return priority == 4;
    }

    Job() : id(0), type(JobType::blur), name(""), isCancelled(false), priority(2), arrivalTime(0), estimatedCost(1.0),targetW(0), targetH(0), startX(0), startY(0), r(0), g(0), b(0), filePath("") 
    {
    }

    Job(int jobId, int jType, const std::string& jName, int p = -1, long long arr = 0, double cost = 1.0): id(jobId), type(jType), name(jName), isCancelled(false),arrivalTime(arr), estimatedCost(cost), targetW(0), targetH(0), startX(0), startY(0), r(0), g(0), b(0), filePath("")
    {

        priority = (p > 0) ? p : defaultPriorityForType(jType);

    }
};
