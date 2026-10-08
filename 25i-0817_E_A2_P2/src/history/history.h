#pragma once
#include <iostream>
#include <string>
#include "../stack.h"
#include "historyRecord.h"
#include "../coreImageFunctions/rotation/applyRotation.h"
#include "../coreImageFunctions/flip/applyFlip.h"
#include "../coreImageFunctions/brightness/applyBrightness.h"

class HistoryManager {
private:
    stackType<HistoryRecord> undoStack;
    stackType<HistoryRecord> redoStack;
    size_t memoryBudgetBytes;
    size_t currentMemoryUsageBytes;
    int discardedRecordsCount;
    int pushCount;
    int popCount;
    long long sequenceCounter;

    Pixel** cloneGrid(Pixel** src, int w, int h) {
        if (!src || w <= 0 || h <= 0) return nullptr;
        Pixel** copy = new Pixel*[h];
        for (int y = 0; y < h; y++) {
            copy[y] = new Pixel[w];
            for (int x = 0; x < w; x++) {
                copy[y][x] = src[y][x];
            }
        }
        return copy;
    }

    void freeGrid(Pixel** grid, int h) {
        if (!grid || h <= 0) return;
        for (int y = 0; y < h; y++) {
            delete[] grid[y];
        }
        delete[] grid;
    }

    void evictOldestRecords(size_t neededBytes) {
        while (currentMemoryUsageBytes + neededBytes > memoryBudgetBytes && !undoStack.isEmptyStack()) {
            HistoryRecord oldest = undoStack.removeBottom();
            currentMemoryUsageBytes = (currentMemoryUsageBytes >= oldest.estimatedMemoryBytes)
                                      ? (currentMemoryUsageBytes - oldest.estimatedMemoryBytes) : 0;
            oldest.freeSavedGrid();
            discardedRecordsCount++;
            std::cout << "[Memory-Aware History] Budget exceeded (" << memoryBudgetBytes / 1024 << " KB). Discarded oldest record: "
                      << oldest.opName << " (Total discarded: " << discardedRecordsCount << ")\n";
        }
    }

    void clearRedoStack() {
        while (!redoStack.isEmptyStack()) {
            HistoryRecord r = redoStack.top();
            redoStack.pop();
            popCount++;
            currentMemoryUsageBytes = (currentMemoryUsageBytes >= r.estimatedMemoryBytes)
                                      ? (currentMemoryUsageBytes - r.estimatedMemoryBytes) : 0;
            r.freeSavedGrid();
        }
    }

public:
    HistoryManager(size_t budgetBytes = 50 * 1024 * 1024, int stackCap = 100)
        : undoStack(stackCap), redoStack(stackCap),
          memoryBudgetBytes(budgetBytes), currentMemoryUsageBytes(0),
          discardedRecordsCount(0), pushCount(0), popCount(0), sequenceCounter(0) {}

    ~HistoryManager() {
        while (!undoStack.isEmptyStack()) {
            HistoryRecord r = undoStack.top();
            undoStack.pop();
            r.freeSavedGrid();
        }
        clearRedoStack();
    }

    void setMemoryBudget(size_t budgetBytes) {
        memoryBudgetBytes = budgetBytes;
        evictOldestRecords(0);
    }

    size_t getMemoryBudget() const { return memoryBudgetBytes; }
    size_t getCurrentMemoryUsage() const { return currentMemoryUsageBytes; }
    int getDiscardedRecordsCount() const { return discardedRecordsCount; }

    // --- Record Compact Operations ---

    // 1. Rotate
    void recordRotate(int angle, int w, int h) {
        clearRedoStack();
        HistoryRecord rec;
        rec.opName = "Rotate " + std::to_string(angle) + " deg";
        rec.opType = HistoryOpType::ROTATE;
        rec.sequenceNumber = ++sequenceCounter;
        rec.angle = angle;
        rec.startX = 0; rec.startY = 0; rec.endX = w; rec.endY = h;
        rec.calculateMemory();

        evictOldestRecords(rec.estimatedMemoryBytes);
        undoStack.push(rec);
        currentMemoryUsageBytes += rec.estimatedMemoryBytes;
        pushCount++;
    }

    // 2. Flip
    void recordFlip(bool horizontal, int w, int h) {
        clearRedoStack();
        HistoryRecord rec;
        rec.opName = horizontal ? "Flip Horizontal" : "Flip Vertical";
        rec.opType = HistoryOpType::FLIP;
        rec.sequenceNumber = ++sequenceCounter;
        rec.isHorizontal = horizontal;
        rec.startX = 0; rec.startY = 0; rec.endX = w; rec.endY = h;
        rec.calculateMemory();

        evictOldestRecords(rec.estimatedMemoryBytes);
        undoStack.push(rec);
        currentMemoryUsageBytes += rec.estimatedMemoryBytes;
        pushCount++;
    }

    // 3. Brightness with Command Coalescing and Clipping Tracking (Section 7.1, 7.2)
    void recordBrightness(double delta, Pixel** beforeImg, int w, int h) {
        clearRedoStack();

        // Scan for clipped pixels in incoming adjustment
        int tempCap = 16;
        int tempCount = 0;
        ClippedPixel* currentClipped = new ClippedPixel[tempCap];

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int nr = static_cast<int>(beforeImg[y][x].r) + static_cast<int>(delta);
                int ng = static_cast<int>(beforeImg[y][x].g) + static_cast<int>(delta);
                int nb = static_cast<int>(beforeImg[y][x].b) + static_cast<int>(delta);
                if (nr < 0 || nr > 255 || ng < 0 || ng > 255 || nb < 0 || nb > 255) {
                    if (tempCount >= tempCap) {
                        int newCap = tempCap * 2;
                        ClippedPixel* newArr = new ClippedPixel[newCap];
                        for (int i = 0; i < tempCount; i++) newArr[i] = currentClipped[i];
                        delete[] currentClipped;
                        currentClipped = newArr;
                        tempCap = newCap;
                    }
                    currentClipped[tempCount++] = {x, y, beforeImg[y][x]};
                }
            }
        }

        // Section 7.2: Coalesce consecutive brightness operations on top of Undo stack
        if (!undoStack.isEmptyStack() && undoStack.top().opType == HistoryOpType::BRIGHTNESS) {
            HistoryRecord topRec = undoStack.top();
            undoStack.pop();

            topRec.brightnessDelta += delta;
            topRec.opName = "Coalesced Brightness (" + std::to_string((int)topRec.brightnessDelta) + ")";

            // Merge clipped pixels without overwriting earlier original values
            for (int i = 0; i < tempCount; i++) {
                bool alreadyTracked = false;
                for (int j = 0; j < topRec.clippedCount; j++) {
                    if (topRec.clippedPixels[j].x == currentClipped[i].x &&
                        topRec.clippedPixels[j].y == currentClipped[i].y) {
                        alreadyTracked = true;
                        break;
                    }
                }
                if (!alreadyTracked) {
                    topRec.addClippedPixel(currentClipped[i]);
                }
            }
            delete[] currentClipped;

            size_t oldMem = topRec.estimatedMemoryBytes;
            topRec.calculateMemory();
            currentMemoryUsageBytes = (currentMemoryUsageBytes >= oldMem) ? (currentMemoryUsageBytes - oldMem) : 0;

            evictOldestRecords(topRec.estimatedMemoryBytes);
            undoStack.push(topRec);
            currentMemoryUsageBytes += topRec.estimatedMemoryBytes;
            std::cout << "[Command Coalescing] Merged brightness adjustment: New total delta = "
                      << topRec.brightnessDelta << "\n";
            return;
        }

        // Otherwise create new Brightness record
        HistoryRecord rec;
        rec.opName = "Brightness (" + std::to_string((int)delta) + ")";
        rec.opType = HistoryOpType::BRIGHTNESS;
        rec.sequenceNumber = ++sequenceCounter;
        rec.brightnessDelta = delta;
        for (int i = 0; i < tempCount; i++) {
            rec.addClippedPixel(currentClipped[i]);
        }
        delete[] currentClipped;

        rec.startX = 0; rec.startY = 0; rec.endX = w; rec.endY = h;
        rec.calculateMemory();

        evictOldestRecords(rec.estimatedMemoryBytes);
        undoStack.push(rec);
        currentMemoryUsageBytes += rec.estimatedMemoryBytes;
        pushCount++;
    }

    // 4. Bucket Fill (Section 7.1)
    void recordBucketFill(Pixel origCol, Pixel newCol, const Point* changed, int changedCount, int w, int h) {
        clearRedoStack();
        HistoryRecord rec;
        rec.opName = "Bucket Fill";
        rec.opType = HistoryOpType::BUCKET_FILL;
        rec.sequenceNumber = ++sequenceCounter;
        rec.originalColor = origCol;
        rec.replacementColor = newCol;
        if (changed && changedCount > 0) {
            for (int i = 0; i < changedCount; i++) {
                rec.addChangedPoint(changed[i]);
            }
        }
        rec.startX = 0; rec.startY = 0; rec.endX = w; rec.endY = h;
        rec.calculateMemory();

        evictOldestRecords(rec.estimatedMemoryBytes);
        undoStack.push(rec);
        currentMemoryUsageBytes += rec.estimatedMemoryBytes;
        pushCount++;
    }

    // 5. Grid-Based Irreversible Operations (Grayscale, Blur, Resize, Crop)
    void recordGridOperation(const std::string& name, int type, Pixel** beforeImg, int w, int h) {
        clearRedoStack();
        HistoryRecord rec;
        rec.opName = name;
        rec.opType = type;
        rec.sequenceNumber = ++sequenceCounter;
        rec.savedGrid = cloneGrid(beforeImg, w, h);
        rec.savedW = w;
        rec.savedH = h;
        rec.startX = 0; rec.startY = 0; rec.endX = w; rec.endY = h;
        rec.calculateMemory();

        evictOldestRecords(rec.estimatedMemoryBytes);
        undoStack.push(rec);
        currentMemoryUsageBytes += rec.estimatedMemoryBytes;
        pushCount++;
    }

    // --- Reverse & Redo Execution ---

    bool undo(Pixel**& currentImg, int& currentW, int& currentH) {
        if (undoStack.isEmptyStack()) return false;

        HistoryRecord rec = undoStack.top();
        undoStack.pop();
        popCount++;
        currentMemoryUsageBytes = (currentMemoryUsageBytes >= rec.estimatedMemoryBytes)
                                  ? (currentMemoryUsageBytes - rec.estimatedMemoryBytes) : 0;

        HistoryRecord redoRec;
        redoRec.sequenceNumber = ++sequenceCounter;
        redoRec.opName = rec.opName;
        redoRec.opType = rec.opType;

        switch (rec.opType) {
            case HistoryOpType::ROTATE: {
                redoRec.angle = rec.angle;
                redoRec.calculateMemory();
                redoStack.push(redoRec);
                currentMemoryUsageBytes += redoRec.estimatedMemoryBytes;

                int invAngle = (360 - (rec.angle % 360)) % 360;
                currentImg = rotateObject::applyRotate(currentImg, currentW, currentH, invAngle);
                break;
            }
            case HistoryOpType::FLIP: {
                redoRec.isHorizontal = rec.isHorizontal;
                redoRec.calculateMemory();
                redoStack.push(redoRec);
                currentMemoryUsageBytes += redoRec.estimatedMemoryBytes;

                if (rec.isHorizontal) {
                    flipAxis::applyFlipHorizontal(currentImg, currentW, currentH);
                } else {
                    flipAxis::applyFlipVertical(currentImg, currentW, currentH);
                }
                break;
            }
            case HistoryOpType::BRIGHTNESS: {
                redoRec.brightnessDelta = rec.brightnessDelta;
                for (int i = 0; i < rec.clippedCount; i++) {
                    redoRec.addClippedPixel(rec.clippedPixels[i]);
                }
                redoRec.calculateMemory();
                redoStack.push(redoRec);
                currentMemoryUsageBytes += redoRec.estimatedMemoryBytes;

                MyBrightness::applyBrightness(currentImg, currentW, currentH, -rec.brightnessDelta);
                for (int i = 0; i < rec.clippedCount; i++) {
                    int cx = rec.clippedPixels[i].x;
                    int cy = rec.clippedPixels[i].y;
                    if (cy >= 0 && cy < currentH && cx >= 0 && cx < currentW) {
                        currentImg[cy][cx] = rec.clippedPixels[i].original;
                    }
                }
                break;
            }
            case HistoryOpType::BUCKET_FILL: {
                redoRec.originalColor = rec.originalColor;
                redoRec.replacementColor = rec.replacementColor;
                for (int i = 0; i < rec.changedCount; i++) {
                    redoRec.addChangedPoint(rec.changedPoints[i]);
                }
                redoRec.calculateMemory();
                redoStack.push(redoRec);
                currentMemoryUsageBytes += redoRec.estimatedMemoryBytes;

                for (int i = 0; i < rec.changedCount; i++) {
                    int px = rec.changedPoints[i].coordinatesX;
                    int py = rec.changedPoints[i].coordinatesY;
                    if (py >= 0 && py < currentH && px >= 0 && px < currentW) {
                        currentImg[py][px] = rec.originalColor;
                    }
                }
                break;
            }
            case HistoryOpType::GRAYSCALE:
            case HistoryOpType::BLUR:
            case HistoryOpType::CROP:
            case HistoryOpType::RESIZE: {
                redoRec.savedGrid = cloneGrid(currentImg, currentW, currentH);
                redoRec.savedW = currentW;
                redoRec.savedH = currentH;
                redoRec.calculateMemory();
                redoStack.push(redoRec);
                currentMemoryUsageBytes += redoRec.estimatedMemoryBytes;

                freeGrid(currentImg, currentH);
                currentImg = cloneGrid(rec.savedGrid, rec.savedW, rec.savedH);
                currentW = rec.savedW;
                currentH = rec.savedH;
                break;
            }
        }

        return true;
    }

    bool redo(Pixel**& currentImg, int& currentW, int& currentH) {
        if (redoStack.isEmptyStack()) return false;

        HistoryRecord rec = redoStack.top();
        redoStack.pop();
        popCount++;
        currentMemoryUsageBytes = (currentMemoryUsageBytes >= rec.estimatedMemoryBytes)
                                  ? (currentMemoryUsageBytes - rec.estimatedMemoryBytes) : 0;

        switch (rec.opType) {
            case HistoryOpType::ROTATE: {
                currentImg = rotateObject::applyRotate(currentImg, currentW, currentH, rec.angle);
                recordRotate(rec.angle, currentW, currentH);
                break;
            }
            case HistoryOpType::FLIP: {
                if (rec.isHorizontal) flipAxis::applyFlipHorizontal(currentImg, currentW, currentH);
                else flipAxis::applyFlipVertical(currentImg, currentW, currentH);
                recordFlip(rec.isHorizontal, currentW, currentH);
                break;
            }
            case HistoryOpType::BRIGHTNESS: {
                MyBrightness::applyBrightness(currentImg, currentW, currentH, rec.brightnessDelta);
                HistoryRecord forwardRec = rec;
                forwardRec.calculateMemory();
                evictOldestRecords(forwardRec.estimatedMemoryBytes);
                undoStack.push(forwardRec);
                currentMemoryUsageBytes += forwardRec.estimatedMemoryBytes;
                break;
            }
            case HistoryOpType::BUCKET_FILL: {
                for (int i = 0; i < rec.changedCount; i++) {
                    int px = rec.changedPoints[i].coordinatesX;
                    int py = rec.changedPoints[i].coordinatesY;
                    if (py >= 0 && py < currentH && px >= 0 && px < currentW) {
                        currentImg[py][px] = rec.replacementColor;
                    }
                }
                HistoryRecord forwardRec = rec;
                forwardRec.calculateMemory();
                evictOldestRecords(forwardRec.estimatedMemoryBytes);
                undoStack.push(forwardRec);
                currentMemoryUsageBytes += forwardRec.estimatedMemoryBytes;
                break;
            }
            case HistoryOpType::GRAYSCALE:
            case HistoryOpType::BLUR:
            case HistoryOpType::CROP:
            case HistoryOpType::RESIZE: {
                HistoryRecord undoRec;
                undoRec.opName = rec.opName;
                undoRec.opType = rec.opType;
                undoRec.savedGrid = cloneGrid(currentImg, currentW, currentH);
                undoRec.savedW = currentW;
                undoRec.savedH = currentH;
                undoRec.calculateMemory();

                evictOldestRecords(undoRec.estimatedMemoryBytes);
                undoStack.push(undoRec);
                currentMemoryUsageBytes += undoRec.estimatedMemoryBytes;

                freeGrid(currentImg, currentH);
                currentImg = cloneGrid(rec.savedGrid, rec.savedW, rec.savedH);
                currentW = rec.savedW;
                currentH = rec.savedH;
                break;
            }
        }

        return true;
    }

    bool canUndo() const { return !undoStack.isEmptyStack(); }
    bool canRedo() const { return !redoStack.isEmptyStack(); }
    int getUndoSize() const { return undoStack.size(); }
    int getRedoSize() const { return redoStack.size(); }
    int getPushCount() const { return pushCount; }
    int getPopCount() const { return popCount; }

    std::string getUndoTopName() const {
        if (undoStack.isEmptyStack()) return "None";
        return undoStack.top().opName;
    }

    std::string getRedoTopName() const {
        if (redoStack.isEmptyStack()) return "None";
        return redoStack.top().opName;
    }

    void printUndoContents() const {
        if (undoStack.isEmptyStack()) {
            std::cout << "[Empty]\n";
            return;
        }
        for (int i = undoStack.size() - 1; i >= 0; i--) {
            std::cout << "[" << undoStack.getAt(i).opName << " ~ "
                      << undoStack.getAt(i).estimatedMemoryBytes << " B] ";
        }
        std::cout << "\n";
    }

    void printRedoContents() const {
        if (redoStack.isEmptyStack()) {
            std::cout << "[Empty]\n";
            return;
        }
        for (int i = redoStack.size() - 1; i >= 0; i--) {
            std::cout << "[" << redoStack.getAt(i).opName << "] ";
        }
        std::cout << "\n";
    }
};
