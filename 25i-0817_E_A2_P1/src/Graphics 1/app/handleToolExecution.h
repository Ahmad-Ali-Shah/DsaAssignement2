#pragma once
#include <string>
#include <iostream>
#include "../types/toolConstants.h"
#include "../../image.h"
#include "../../coreImageFunctions/rotation.h"
#include "../../coreImageFunctions/flip.h"
#include "../../coreImageFunctions/brightness.h"
#include "../../coreImageFunctions/greyScale.h"
#include "../../coreImageFunctions/crop.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"
#include "../../read/read.h"
#include "../../read/write.h"
#include "../../read/delete.h"

namespace GraphicsApp {
    void handleToolExecution(int toolId, Pixel**& img, int& width, int& height, HistoryManager& history, ProcessingPipeline& pipeline, bool& showInspector, std::string& lastAction) {
        if (toolId == GraphicsTool::load) {
            std::cout << "\n[GUI] Enter path of image to load (PPM, PNG, JPG): ";
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
        else if (toolId == GraphicsTool::rotate90) {
            if (!img) return;
            history.recordAction("Rotate 90", img, width, height);
            img = rotateObject::applyRotate(img, width, height, 90);
            lastAction = "Rotated 90 degrees";
        }
        else if (toolId == GraphicsTool::flipH) {
            if (!img) return;
            history.recordAction("Flip Horizontal", img, width, height);
            flipAxis::applyFlipHorizontal(img, width, height);
            lastAction = "Flipped Horizontally";
        }
        else if (toolId == GraphicsTool::brightnessUp) {
            if (!img) return;
            history.recordAction("Brightness", img, width, height);
            MyBrightness::applyBrightness(img, width, height, 20.0);
            lastAction = "Brightness +20";
        }
        else if (toolId == GraphicsTool::grayscale) {
            if (!img) return;
            history.recordAction("Grayscale", img, width, height);
            MygreyScale::applyGrayscale(img, width, height);
            lastAction = "Applied Grayscale";
        }
        else if (toolId == GraphicsTool::crop) {
            if (!img || width <= 10 || height <= 10) return;
            history.recordAction("Crop", img, width, height);
            int newW = width / 2;
            int newH = height / 2;
            img = myCrop::applyCrop(img, width, height, 0, 0, newW, newH);
            lastAction = "Cropped region (50%)";
        }
        else if (toolId == GraphicsTool::undo) {
            if (history.canUndo()) {
                history.undo(img, width, height);
                lastAction = "Undo executed";
            }
        }
        else if (toolId == GraphicsTool::redo) {
            if (history.canRedo()) {
                history.redo(img, width, height);
                lastAction = "Redo executed";
            }
        }
        else if (toolId == GraphicsTool::enqueueResize) {
            Job j(0, JobType::resize, "Resize 320x320");
            j.targetW = 320;
            j.targetH = 320;
            pipeline.addJob(j);
            lastAction = "Enqueued Resize";
        }
        else if (toolId == GraphicsTool::enqueueBlur) {
            Job j(0, JobType::blur, "Blur (3x3 Kernel)");
            pipeline.addJob(j);
            lastAction = "Enqueued Blur";
        }
        else if (toolId == GraphicsTool::enqueueBucketStack) {
            Job j(0, JobType::bucketFillStack, "Fill (Stack DFS)");
            j.startX = width / 2;
            j.startY = height / 2;
            j.r = 255; j.g = 100; j.b = 50;
            pipeline.addJob(j);
            lastAction = "Enqueued Stack Fill";
        }
        else if (toolId == GraphicsTool::enqueueBucketQueue) {
            Job j(0, JobType::bucketFillQueue, "Fill (Queue BFS)");
            j.startX = width / 2;
            j.startY = height / 2;
            j.r = 50; j.g = 150; j.b = 255;
            pipeline.addJob(j);
            lastAction = "Enqueued Queue Fill";
        }
        else if (toolId == GraphicsTool::processNext) {
            pipeline.processNextJob(img, width, height, history);
            lastAction = "Processed next job";
        }
        else if (toolId == GraphicsTool::processAll) {
            pipeline.processAllJobs(img, width, height, history);
            lastAction = "Processed all pending jobs";
        }
        else if (toolId == GraphicsTool::clearPipeline) {
            pipeline.clearQueue();
            lastAction = "Cleared pipeline";
        }
        else if (toolId == GraphicsTool::toggleInspector) {
            showInspector = !showInspector;
        }
    }
}
