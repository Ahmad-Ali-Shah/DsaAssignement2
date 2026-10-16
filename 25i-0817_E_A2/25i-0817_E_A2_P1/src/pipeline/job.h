#pragma once
#include <string>

////////////////////

// as mentioned in assignment 

// each operation is concidred as job 

///////////////////////////////


namespace JobType {
    const int resize = 1;
    const int blur = 2;
    const int bucketFillStack = 3;
    const int bucketFillQueue = 4;
    const int saveProject = 5;
    const int exportImage = 6;
}

struct Job {
    int id;
    int type;
    std::string name;
    bool isCancelled;

    // Parameters
    int targetW, targetH;
    int startX, startY;
    unsigned int r, g, b;
    std::string filePath;

    Job() : id(0), type(JobType::blur), name(""), isCancelled(false), targetW(0), targetH(0), startX(0), startY(0), r(0), g(0), b(0), filePath("") {}
    Job(int jobId, int jType, const std::string& jName): id(jobId), type(jType), name(jName), isCancelled(false), targetW(0), targetH(0), startX(0), startY(0), r(0), g(0), b(0), filePath("") {}
};
