#pragma once
#include <string>
#include "../../image.h"
#include "../../history/history.h"
#include "../../coreImageFunctions/rotation.h"
#include "../../coreImageFunctions/flip.h"
#include "../../coreImageFunctions/brightness.h"
#include "../../coreImageFunctions/greyScale.h"
#include "../../coreImageFunctions/blur.h"
#include "../../coreImageFunctions/crop.h"
#include "../../coreImageFunctions/resize.h"
#include "../../coreImageFunctions/bucketFill/bucketFillQueueBased.h"
#include "../../read/mainLogic/writer.h"
#include "editorConstants.h"

namespace EditorPage {

    bool executeEditorAction(int op, Pixel**& img, int& width, int& height, HistoryManager& history, const std::string& p1, const std::string& p2, std::string& currentOperation) {
        if (!img || width <= 0 || height <= 0) return false;

        bool changed = false;

        if (op == EditorConstants::opRot90) {
            history.recordAction("Rotate 90", img, width, height);
            img = rotateObject::applyRotate(img, width, height, 90);
            currentOperation = "Rotations 90";
            changed = true;
        } else if (op == EditorConstants::opRot180) {
            history.recordAction("Rotate 180", img, width, height);
            img = rotateObject::applyRotate(img, width, height, 180);
            currentOperation = "Rotations 180";
            changed = true;
        } else if (op == EditorConstants::opRot270) {
            history.recordAction("Rotate 270", img, width, height);
            img = rotateObject::applyRotate(img, width, height, 270);
            currentOperation = "Rotations 270";
            changed = true;
        } else if (op == EditorConstants::opRot360) {
            history.recordAction("Rotate 360", img, width, height);
            currentOperation = "Rotations 360";
            changed = true;
        } else if (op == EditorConstants::opFlipH) {
            history.recordAction("Flip Horizontal", img, width, height);
            flipAxis::applyFlipHorizontal(img, width, height);
            currentOperation = "Horizontal Flip";
            changed = true;
        } else if (op == EditorConstants::opFlipV) {
            history.recordAction("Flip Vertical", img, width, height);
            flipAxis::applyFlipVertical(img, width, height);
            currentOperation = "Vertical Flip";
            changed = true;
        } else if (op == EditorConstants::opGrayscale) {
            history.recordAction("Grayscale", img, width, height);
            MygreyScale::applyGrayscale(img, width, height);
            currentOperation = "Grayscale";
            changed = true;
        } else if (op == EditorConstants::opBrightness) {
            double delta = 30.0;
            if (!p1.empty()) {
                delta = static_cast<double>(std::stoi(p1));
            }
            history.recordAction("Brightness", img, width, height);
            MyBrightness::applyBrightness(img, width, height, delta);
            currentOperation = "Brightness " + std::to_string(static_cast<int>(delta));
            changed = true;
        } else if (op == EditorConstants::opBlur) {
            history.recordAction("Blur", img, width, height);
            FrobeniusMatrixInnerProductForBlurr::applyBlur(img, width, height);
            currentOperation = "Box Blur";
            changed = true;
        } else if (op == EditorConstants::opResize) {
            history.recordAction("Resize", img, width, height);
            int newW = width / 2;
            int newH = height / 2;
            if (newW < 2) newW = 2;
            if (newH < 2) newH = 2;
            img = scaling::applyResize(img, width, height, newW, newH);
            currentOperation = "Resize (" + std::to_string(width) + "x" + std::to_string(height) + ")";
            changed = true;
        } else if (op == EditorConstants::opCrop) {
            int cw = width / 2;
            int ch = height / 2;
            if (!p1.empty() && !p2.empty()) {
                cw = std::stoi(p1);
                ch = std::stoi(p2);
                if (cw > width) cw = width;
                if (ch > height) ch = height;
            }
            history.recordAction("Crop", img, width, height);
            img = myCrop::applyCrop(img, width, height, 0, 0, cw, ch);
            currentOperation = "Crop (" + std::to_string(cw) + "x" + std::to_string(ch) + ")";
            changed = true;
        } else if (op == EditorConstants::opBucketFill) {
            history.recordAction("Bucket Fill", img, width, height);
            MybucketFill::ReplaceNearOneQueue(img, static_cast<double>(width), static_cast<double>(height), width / 2, height / 2, 255, 120, 80);
            currentOperation = "Bucket Fill (Queue)";
            changed = true;
        } else if (op == EditorConstants::opSave) {
            std::string outPath = p1.empty() ? "25i-0817_E_A2_P1/images/output.png" : p1;
            ReadPath::WriteImage(outPath, img, width, height);
            currentOperation = "Saved to " + outPath;
            return true;
        }

        return changed;
    }

}
