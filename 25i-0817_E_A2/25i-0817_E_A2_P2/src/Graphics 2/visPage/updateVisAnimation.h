#pragma once
#include <string>
#include <iostream>
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"
#include "../../coreImageFunctions/rotation.h"
#include "../../coreImageFunctions/greyScale.h"
#include "../../coreImageFunctions/blur.h"
#include "../../coreImageFunctions/brightness.h"
#include "../canvas/createTextureFromPixels.h"
#include "visConstants.h"

namespace VisPage {

    void updateVisAnimation(VisConstants::VisAnimController& anim,
                            float dt,
                            Pixel**& img,
                            int& width,
                            int& height,
                            sf::Texture& canvasTex,
                            std::string mainStack[],
                            int& mainTop,
                            std::string auxStack[],
                            int& auxTop,
                            std::string queueArr[],
                            int& queueFront,
                            int& queueRear,
                            int& queueCount,
                            std::string& currentOp,
                            std::string& statusMsg) {
        if (anim.animType == VisConstants::animIdle) return;

        anim.timer += dt;
        if (anim.timer < anim.stepDuration) return;

        anim.timer -= anim.stepDuration;
        anim.currentStep++;

        // 1. Stack Animation: Clear Stack A -> Save in Other Stack B -> Re-push to Stack A
        if (anim.animType == VisConstants::animStackPopPush) {
            if (anim.currentStep >= 1 && anim.currentStep <= 5) {
                if (mainTop >= 0) {
                    std::string item = mainStack[mainTop];
                    mainTop--;
                    auxTop++;
                    auxStack[auxTop] = item;
                    statusMsg = "Popped [" + item + "] from Stack A -> Pushed into Other Stack B (Index " + std::to_string(auxTop) + ")";
                    currentOp = "Pop: " + item;
                }
            } else if (anim.currentStep == 6) {
                statusMsg = "Stack A CLEARED! Now reversing: Popping from Other Stack B to re-push into Stack A...";
                currentOp = "Stack A Cleared";
            } else if (anim.currentStep >= 7 && anim.currentStep <= 11) {
                if (auxTop >= 0) {
                    std::string item = auxStack[auxTop];
                    auxTop--;
                    mainTop++;
                    mainStack[mainTop] = item;
                    statusMsg = "Popped [" + item + "] from Other Stack B -> Re-pushed into Stack A (Index " + std::to_string(mainTop) + ")";
                    currentOp = "Re-push: " + item;
                }
            } else {
                anim.animType = VisConstants::animIdle;
                statusMsg = "Animation Complete: Array cleared, stored in other stack, and refilled!";
                currentOp = "Current Image";
            }
        }
        // 2. Queue Animation: Dequeue and Enqueue circular cycle
        else if (anim.animType == VisConstants::animQueueProcess) {
            if (anim.currentStep <= 4) {
                if (queueCount > 0) {
                    std::string item = queueArr[queueFront];
                    queueFront = (queueFront + 1) % 8;
                    queueCount--;
                    statusMsg = "Dequeued [" + item + "] from FRONT of circular array.";
                    currentOp = "Dequeue Front";
                }
            } else if (anim.currentStep <= 8) {
                if (queueCount < 8) {
                    queueRear = (queueRear + 1) % 8;
                    queueArr[queueRear] = "Task #" + std::to_string(anim.currentStep);
                    queueCount++;
                    statusMsg = "Enqueued [Task #" + std::to_string(anim.currentStep) + "] at REAR (Index " + std::to_string(queueRear) + ").";
                    currentOp = "Enqueue Rear";
                }
            } else {
                anim.animType = VisConstants::animIdle;
                statusMsg = "Queue Animation Complete: Circular array operations finished.";
                currentOp = "Current Image";
            }
        }
        // 3. Image Pipeline Animation: Rotation -> Grayscale -> Blur -> Brightness
        else if (anim.animType == VisConstants::animImageSteps) {
            if (!img || width <= 0 || height <= 0) {
                anim.animType = VisConstants::animIdle;
                return;
            }

            if (anim.currentStep == 1) {
                currentOp = "Rotations 90";
                statusMsg = "Pipeline Step 1: Applying 90 Degree Rotation";
                img = rotateObject::applyRotate(img, width, height, 90);
                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
            } else if (anim.currentStep == 2) {
                currentOp = "Grayscale";
                statusMsg = "Pipeline Step 2: Applying Grayscale Conversion";
                MygreyScale::applyGrayscale(img, width, height);
                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
            } else if (anim.currentStep == 3) {
                currentOp = "Box Blur";
                statusMsg = "Pipeline Step 3: Applying 3x3 Box Blur Filter";
                FrobeniusMatrixInnerProductForBlurr::applyBlur(img, width, height);
                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
            } else if (anim.currentStep == 4) {
                currentOp = "Brightness 35";
                statusMsg = "Pipeline Step 4: Applying Brightness Boost (+35)";
                MyBrightness::applyBrightness(img, width, height, 35.0);
                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
            } else if (anim.currentStep >= 5) {
                anim.animType = VisConstants::animIdle;
                currentOp = "Pipeline Complete";
                statusMsg = "Image Pipeline Complete: All 4 transformations applied.";
            }
        }
    }

}
