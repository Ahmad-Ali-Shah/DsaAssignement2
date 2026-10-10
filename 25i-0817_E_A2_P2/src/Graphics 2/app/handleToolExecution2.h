#pragma once
#include <string>
#include <iostream>
#include "../types/priorityConstants.h"
#include "../../image.h"
#include "../../coreImageFunctions/rotation/applyRotation.h"
#include "../../coreImageFunctions/flip/applyFlip.h"
#include "../../coreImageFunctions/brightness/applyBrightness.h"
#include "../../coreImageFunctions/greyScale/applyGreyScale.h"
#include "../../coreImageFunctions/Crop/applyCrop.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"
#include "../../read/read.h"
#include "../../read/write.h"
#include "../../read/delete.h"

namespace GraphicsApp2 {
    void handleToolExecution2(int toolId, Pixel**& img, int& width, int& height, HistoryManager& history, ProcessingPipeline& pipeline, bool& showDualFill, bool& showBenchmark, std::string& lastAction) {
        if (toolId == GraphicsTool2::LOAD) {
            std::cout << "\n[GUI P2] Enter path of image to load (PPM, PNG, JPG): ";
            std::string path;
            std::cin >> path;
            int newW = 0, newH = 0;
            Pixel** newImg = ReadPath::Read(path, newW, newH);
            if (newImg) {
                if (img) ReadPath::freeImage(img, height);
                img = newImg;
                width = newW;
                height = newH;
                lastAction = "Loaded image from " + path;
            }
        }
        else if (toolId == GraphicsTool2::ROTATE_90) {
            if (!img) return;
            history.recordRotate(90, width, height);
            img = rotateObject::applyRotate(img, width, height, 90);
            lastAction = "Rotated 90 degrees";
        }
        else if (toolId == GraphicsTool2::FLIP_H) {
            if (!img) return;
            history.recordFlip(true, width, height);
            flipAxis::applyFlipHorizontal(img, width, height);
            lastAction = "Flipped Horizontally";
        }
        else if (toolId == GraphicsTool2::BRIGHTNESS_UP) {
            if (!img) return;
            history.recordBrightness(20.0, img, width, height);
            MyBrightness::applyBrightness(img, width, height, 20.0);
            lastAction = "Brightness +20 (Coalescable)";
        }
        else if (toolId == GraphicsTool2::GRAYSCALE) {
            if (!img) return;
            history.recordGridOperation("Grayscale", HistoryOpType::GRAYSCALE, img, width, height);
            MygreyScale::applyGrayscale(img, width, height);
            lastAction = "Applied Grayscale";
        }
        else if (toolId == GraphicsTool2::CROP) {
            if (!img || width <= 10 || height <= 10) return;
            int newW = width / 2;
            int newH = height / 2;
            history.recordGridOperation("Crop", HistoryOpType::CROP, img, width, height);
            img = myCrop::applyCrop(img, width, height, 0, 0, newW, newH);
            lastAction = "Cropped region (50%)";
        }
        else if (toolId == GraphicsTool2::UNDO) {
            if (history.canUndo()) {
                history.undo(img, width, height);
                lastAction = "Undo executed";
            }
        }
        else if (toolId == GraphicsTool2::REDO) {
            if (history.canRedo()) {
                history.redo(img, width, height);
                lastAction = "Redo executed";
            }
        }
        else if (toolId == GraphicsTool2::ENQUEUE_RESIZE) {
            Job j(0, JobType::RESIZE, "Resize 320x320", 3, 0, 60.0);
            j.targetW = 320;
            j.targetH = 320;
            pipeline.addJob(j);
            lastAction = "Enqueued Priority-3 Resize";
        }
        else if (toolId == GraphicsTool2::ENQUEUE_BLUR) {
            Job j(0, JobType::BLUR, "Blur (Radius 2)", 2, 0, 40.0);
            pipeline.addJob(j);
            lastAction = "Enqueued Priority-2 Blur";
        }
        else if (toolId == GraphicsTool2::ENQUEUE_BUCKET_STACK) {
            Job j(0, JobType::BUCKET_FILL_STACK, "Bucket Fill (Stack DFS)", 2, 0, 25.0);
            j.startX = width / 2;
            j.startY = height / 2;
            j.r = 255; j.g = 120; j.b = 50;
            pipeline.addJob(j);
            lastAction = "Enqueued Priority-2 Fill (Stack)";
        }
        else if (toolId == GraphicsTool2::ENQUEUE_BUCKET_QUEUE) {
            Job j(0, JobType::BUCKET_FILL_QUEUE, "Bucket Fill (Queue BFS)", 2, 0, 25.0);
            j.startX = width / 2;
            j.startY = height / 2;
            j.r = 50; j.g = 180; j.b = 255;
            pipeline.addJob(j);
            lastAction = "Enqueued Priority-2 Fill (Queue)";
        }
        else if (toolId == GraphicsTool2::ENQUEUE_SAVE) {
            Job j(0, JobType::SAVE_PROJECT, "Save Project (Barrier)", 4, 0, 100.0);
            j.filePath = "project_save.ppm";
            pipeline.addJob(j);
            lastAction = "Enqueued Barrier: Save Project";
        }
        else if (toolId == GraphicsTool2::ENQUEUE_EXPORT) {
            Job j(0, JobType::EXPORT_IMAGE, "Export PNG (Barrier)", 4, 0, 100.0);
            j.filePath = "export_output.png";
            pipeline.addJob(j);
            lastAction = "Enqueued Barrier: Export PNG";
        }
        else if (toolId == GraphicsTool2::PROCESS_NEXT) {
            pipeline.processNextJob(img, width, height, history);
            lastAction = "Dispatched highest-priority job";
        }
        else if (toolId == GraphicsTool2::PROCESS_ALL) {
            pipeline.processAllJobs(img, width, height, history);
            lastAction = "Dispatched all scheduled jobs";
        }
        else if (toolId == GraphicsTool2::TOGGLE_MODE) {
            int newMode = (pipeline.getMode() == SchedulerMode::FIFO) ? SchedulerMode::PRIORITY : SchedulerMode::FIFO;
            pipeline.setMode(newMode);
            lastAction = (newMode == SchedulerMode::FIFO) ? "Mode: FIFO" : "Mode: PRIORITY";
        }
        else if (toolId == GraphicsTool2::RUN_BENCHMARK) {
            showBenchmark = !showBenchmark;
        }
        else if (toolId == GraphicsTool2::TOGGLE_DUAL_FILL) {
            showDualFill = !showDualFill;
        }
        else if (toolId == GraphicsTool2::CLEAR_PIPELINE) {
            pipeline.clearQueue();
            lastAction = "Cleared pipeline";
        }
    }
}
