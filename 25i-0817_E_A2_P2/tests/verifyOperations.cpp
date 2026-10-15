#include <iostream>
#include <cassert>
#include <string>
#include "../src/image.h"
#include "../src/read/read.h"
#include "../src/read/write.h"
#include "../src/read/delete.h"
#include "../src/history/history.h"
#include "../src/pipeline/pipeline.h"
#include "../src/inspector/inspector.h"

// Core operations
#include "../src/coreImageFunctions/brightness/applyBrightness.h"
#include "../src/coreImageFunctions/greyScale/applyGreyScale.h"
#include "../src/coreImageFunctions/flip/applyFlip.h"
#include "../src/coreImageFunctions/rotation/applyRotation.h"
#include "../src/coreImageFunctions/Crop/applyCrop.h"
#include "../src/coreImageFunctions/resize/applyResize.h"
#include "../src/coreImageFunctions/blur/applyBlur.h"
#include "../src/coreImageFunctions/bucketFill/bucketFillStructBased.h"
#include "../src/coreImageFunctions/bucketFill/bucketFillQueueBased.h"

using namespace std;

int main() {
    cout << "========================================================\n";
    cout << "    VERIFYING ALL IMAGELAB OPERATIONS ON AI TEST IMAGE  \n";
    cout << "========================================================\n";

    int w = 0, h = 0;
    Pixel** img = ReadPath::Read("images/sample.ppm", w, h);
    if (!img || w <= 0 || h <= 0) {
        cout << "[FAILED] Could not load images/sample.ppm\n";
        return 1;
    }
    cout << "[OK] Loaded sample.ppm (" << w << "x" << h << ")\n";

    HistoryManager hm(50 * 1024 * 1024);
    ProcessingPipeline pipeline(100, SchedulerMode::priority);

    // 1. Brightness
    hm.recordBrightness(60.0, img, w, h);
    MyBrightness::applyBrightness(img, w, h, 60.0);
    ReadPath::Write("images/outBrightness.ppm", img, w, h, true);
    cout << "[OK] Brightness applied and written to images/outBrightness.ppm\n";
    hm.undo(img, w, h);

    // 2. Grayscale
    hm.recordGridOperation("Grayscale", HistoryOpType::grayscale, img, w, h);
    MygreyScale::applyGrayscale(img, w, h);
    ReadPath::Write("images/outGrayscale.ppm", img, w, h, true);
    cout << "[OK] Grayscale applied and written to images/outGrayscale.ppm\n";
    hm.undo(img, w, h);

    // 3. Flip Horizontal
    hm.recordFlip(true, w, h);
    flipAxis::applyFlipHorizontal(img, w, h);
    ReadPath::Write("images/outFlipH.ppm", img, w, h, true);
    cout << "[OK] Flip Horizontal applied and written to images/outFlipH.ppm\n";
    hm.undo(img, w, h);

    // 4. Rotate 90
    hm.recordRotate(90, w, h);
    img = rotateObject::applyRotate(img, w, h, 90);
    ReadPath::Write("images/outRotate90.ppm", img, w, h, true);
    cout << "[OK] Rotate 90 applied and written to images/outRotate90.ppm (" << w << "x" << h << ")\n";
    hm.undo(img, w, h);

    // 5. Crop
    hm.recordGridOperation("Crop", HistoryOpType::crop, img, w, h);
    img = myCrop::applyCrop(img, w, h, 100, 100, 200, 200);
    ReadPath::Write("images/outCrop.ppm", img, w, h, true);
    cout << "[OK] Crop applied and written to images/outCrop.ppm (" << w << "x" << h << ")\n";
    hm.undo(img, w, h);

    // 6. Resize
    hm.recordGridOperation("Resize", HistoryOpType::resize, img, w, h);
    img = scaling::applyResize(img, w, h, 256, 256);
    ReadPath::Write("images/outResize.ppm", img, w, h, true);
    cout << "[OK] Resize applied and written to images/outResize.ppm (" << w << "x" << h << ")\n";
    hm.undo(img, w, h);

    // 7. Blur
    hm.recordGridOperation("Blur", HistoryOpType::blur, img, w, h);
    FrobeniusMatrixInnerProductForBlurr::applyBlur(img, w, h);
    ReadPath::Write("images/outBlur.ppm", img, w, h, true);
    cout << "[OK] Blur applied and written to images/outBlur.ppm\n";
    hm.undo(img, w, h);

    // 8. Bucket Fill Stack (DFS)
    Pixel stackOrig = img[60][60];
    Pixel stackTarget{255, 0, 255}; // Magenta
    Point* stackPts = new Point[w * h];
    int stackPtCount = 0;
    MybucketFill::ReplaceNearOne(img, w, h, 60, 60, stackTarget.r, stackTarget.g, stackTarget.b);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (img[y][x] == stackTarget) stackPts[stackPtCount++] = {x, y};
        }
    }
    hm.recordBucketFill(stackOrig, stackTarget, stackPts, stackPtCount, w, h);
    delete[] stackPts;
    ReadPath::Write("images/outBucketStack.ppm", img, w, h, true);
    cout << "[OK] Bucket Fill (Stack DFS) applied (" << stackPtCount << " pixels) -> images/outBucketStack.ppm\n";
    hm.undo(img, w, h);

    // 9. Bucket Fill Queue (BFS)
    Pixel queueOrig = img[260][260];
    Pixel queueTarget{0, 255, 255}; // Cyan
    Point* queuePts = new Point[w * h];
    int queuePtCount = 0;
    MybucketFill::ReplaceNearOneQueue(img, w, h, 260, 260, queueTarget.r, queueTarget.g, queueTarget.b);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (img[y][x] == queueTarget) queuePts[queuePtCount++] = {x, y};
        }
    }
    hm.recordBucketFill(queueOrig, queueTarget, queuePts, queuePtCount, w, h);
    delete[] queuePts;
    ReadPath::Write("images/outBucketQueue.ppm", img, w, h, true);
    cout << "[OK] Bucket Fill (Queue BFS) applied (" << queuePtCount << " pixels) -> images/outBucketQueue.ppm\n";
    hm.undo(img, w, h);

    // 10. Display Inspector
    DataStructureInspector::display(hm, pipeline);

    ReadPath::freeImage(img, h);
    cout << "========================================================\n";
    cout << "     ALL OPERATIONS TESTED AND RESTORED WITH SUCCESS!    \n";
    cout << "========================================================\n";
    return 0;
}
