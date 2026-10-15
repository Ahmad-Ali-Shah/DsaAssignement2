#pragma once
#include <string>

////////////////////

// as mentioned in assignment 

// each operation is concidred as job 

///////////////////////////////


namespace JobType {

    const int RESIZE = 1;

    const int BLUR = 2;

    const int BUCKET_FILL_STACK = 3;

    const int BUCKET_FILL_QUEUE = 4;

    const int SAVE_PROJECT = 5;

    const int EXPORT_IMAGE = 6;

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


    Job() : id(0), type(JobType::BLUR), name(""), isCancelled(false), targetW(0), targetH(0), startX(0), startY(0), r(0), g(0), b(0), filePath("") {}

    Job(int jobId, int jType, const std::string& jName): id(jobId), type(jType), name(jName), isCancelled(false), targetW(0), targetH(0), startX(0), startY(0), r(0), g(0), b(0), filePath("") {}
};
