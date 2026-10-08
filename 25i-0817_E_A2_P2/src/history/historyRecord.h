#pragma once
#include <string>
#include "../image.h"

// History Operation integer constants (no enum)
namespace HistoryOpType {
    const int ROTATE = 1;
    const int FLIP = 2;
    const int BRIGHTNESS = 3;
    const int CROP = 4;
    const int BUCKET_FILL = 5;
    const int GRAYSCALE = 6;
    const int BLUR = 7;
    const int RESIZE = 8;
}

struct ClippedPixel {
    int x;
    int y;
    Pixel original;
};

struct HistoryRecord {
    std::string opName;
    int opType;
    long long sequenceNumber;
    size_t estimatedMemoryBytes;

    // Affected region bounding box
    int startX, startY;
    int endX, endY;

    // 1. Rotate & Flip parameters
    int angle;
    bool isHorizontal;

    // 2. Brightness parameters & clipped pixels array (custom dynamic array)
    double brightnessDelta;
    ClippedPixel* clippedPixels;
    int clippedCount;
    int clippedCapacity;

    // 3. Bucket fill parameters & changed points array (custom dynamic array)
    Pixel originalColor;
    Pixel replacementColor;
    Point* changedPoints;
    int changedCount;
    int changedCapacity;

    // 4. Irreversible operations (Grayscale, Blur, Resize, Crop)
    Pixel** savedGrid;
    int savedW;
    int savedH;

    void addClippedPixel(const ClippedPixel& cp) {
        if (clippedCount >= clippedCapacity) {
            int newCap = (clippedCapacity == 0) ? 8 : clippedCapacity * 2;
            ClippedPixel* newArr = new ClippedPixel[newCap];
            for (int i = 0; i < clippedCount; i++) {
                newArr[i] = clippedPixels[i];
            }
            delete[] clippedPixels;
            clippedPixels = newArr;
            clippedCapacity = newCap;
        }
        clippedPixels[clippedCount++] = cp;
    }

    void addChangedPoint(const Point& pt) {
        if (changedCount >= changedCapacity) {
            int newCap = (changedCapacity == 0) ? 16 : changedCapacity * 2;
            Point* newArr = new Point[newCap];
            for (int i = 0; i < changedCount; i++) {
                newArr[i] = changedPoints[i];
            }
            delete[] changedPoints;
            changedPoints = newArr;
            changedCapacity = newCap;
        }
        changedPoints[changedCount++] = pt;
    }

    void freeSavedGrid() {
        if (savedGrid && savedH > 0) {
            for (int y = 0; y < savedH; y++) {
                delete[] savedGrid[y];
            }
            delete[] savedGrid;
            savedGrid = nullptr;
            savedW = 0;
            savedH = 0;
        }
    }

    void calculateMemory() {
        estimatedMemoryBytes = sizeof(HistoryRecord);
        if (clippedCapacity > 0) {
            estimatedMemoryBytes += (size_t)clippedCapacity * sizeof(ClippedPixel);
        }
        if (changedCapacity > 0) {
            estimatedMemoryBytes += (size_t)changedCapacity * sizeof(Point);
        }
        if (savedGrid && savedW > 0 && savedH > 0) {
            estimatedMemoryBytes += (size_t)savedW * savedH * sizeof(Pixel);
            estimatedMemoryBytes += (size_t)savedH * sizeof(Pixel*);
        }
    }

    void copyFrom(const HistoryRecord& other) {
        opName = other.opName;
        opType = other.opType;
        sequenceNumber = other.sequenceNumber;
        estimatedMemoryBytes = other.estimatedMemoryBytes;
        startX = other.startX; startY = other.startY;
        endX = other.endX; endY = other.endY;
        angle = other.angle;
        isHorizontal = other.isHorizontal;
        brightnessDelta = other.brightnessDelta;

        clippedCount = other.clippedCount;
        clippedCapacity = other.clippedCapacity;
        if (clippedCapacity > 0 && other.clippedPixels) {
            clippedPixels = new ClippedPixel[clippedCapacity];
            for (int i = 0; i < clippedCount; i++) {
                clippedPixels[i] = other.clippedPixels[i];
            }
        } else {
            clippedPixels = nullptr;
        }

        originalColor = other.originalColor;
        replacementColor = other.replacementColor;
        changedCount = other.changedCount;
        changedCapacity = other.changedCapacity;
        if (changedCapacity > 0 && other.changedPoints) {
            changedPoints = new Point[changedCapacity];
            for (int i = 0; i < changedCount; i++) {
                changedPoints[i] = other.changedPoints[i];
            }
        } else {
            changedPoints = nullptr;
        }

        savedW = other.savedW;
        savedH = other.savedH;
        if (other.savedGrid && savedW > 0 && savedH > 0) {
            savedGrid = new Pixel*[savedH];
            for (int y = 0; y < savedH; y++) {
                savedGrid[y] = new Pixel[savedW];
                for (int x = 0; x < savedW; x++) {
                    savedGrid[y][x] = other.savedGrid[y][x];
                }
            }
        } else {
            savedGrid = nullptr;
        }
    }

    void cleanup() {
        delete[] clippedPixels;
        clippedPixels = nullptr;
        clippedCount = 0;
        clippedCapacity = 0;

        delete[] changedPoints;
        changedPoints = nullptr;
        changedCount = 0;
        changedCapacity = 0;

        freeSavedGrid();
    }

    HistoryRecord()
        : opName(""), opType(HistoryOpType::BRIGHTNESS), sequenceNumber(0), estimatedMemoryBytes(sizeof(HistoryRecord)),
          startX(0), startY(0), endX(0), endY(0),
          angle(0), isHorizontal(false), brightnessDelta(0.0),
          clippedPixels(nullptr), clippedCount(0), clippedCapacity(0),
          originalColor{0,0,0}, replacementColor{0,0,0},
          changedPoints(nullptr), changedCount(0), changedCapacity(0),
          savedGrid(nullptr), savedW(0), savedH(0) {}

    HistoryRecord(const HistoryRecord& other) {
        copyFrom(other);
    }

    HistoryRecord& operator=(const HistoryRecord& other) {
        if (this != &other) {
            cleanup();
            copyFrom(other);
        }
        return *this;
    }

    ~HistoryRecord() {
        cleanup();
    }
};
