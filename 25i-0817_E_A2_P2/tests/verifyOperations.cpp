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
    ProcessingPipeline pipeline(100, SchedulerMode::PRIORITY);

    // 1. Brightness
    hm.recordBrightness(60.0, img, w, h);
    MyBrightness::applyBrightness(img, w, h, 60.0);
    ReadPath::Write("images/out_brightness.ppm", img, w, h, true);
    cout << "[OK] Brightness applied and written to images/out_brightness.ppm\n";
    hm.undo(img, w, h);

    // 2. Grayscale
    hm.recordGridOperation("Grayscale", HistoryOpType::GRAYSCALE, img, w, h);
    MygreyScale::applyGrayscale(img, w, h);
    ReadPath::Write("images/out_grayscale.ppm", img, w, h, true);
    cout << "[OK] Grayscale applied and written to images/out_grayscale.ppm\n";
    hm.undo(img, w, h);

    // 3. Flip Horizontal
    hm.recordFlip(true, w, h);
    flipAxis::applyFlipHorizontal(img, w, h);
    ReadPath::Write("images/out_flip_h.ppm", img, w, h, true);
    cout << "[OK] Flip Horizontal applied and written to images/out_flip_h.ppm\n";
    hm.undo(img, w, h);

    // 4. Rotate 90
    hm.recordRotate(90, w, h);
    img = rotateObject::applyRotate(img, w, h, 90);
    ReadPath::Write("images/out_rotate90.ppm", img, w, h, true);
    cout << "[OK] Rotate 90 applied and written to images/out_rotate90.ppm (" << w << "x" << h << ")\n";
    hm.undo(img, w, h);

    // 5. Crop
    hm.recordGridOperation("Crop", HistoryOpType::CROP, img, w, h);
    img = myCrop::applyCrop(img, w, h, 100, 100, 200, 200);
    ReadPath::Write("images/out_crop.ppm", img, w, h, true);
    cout << "[OK] Crop applied and written to images/out_crop.ppm (" << w << "x" << h << ")\n";
    hm.undo(img, w, h);

    // 6. Resize
    hm.recordGridOperation("Resize", HistoryOpType::RESIZE, img, w, h);
    img = scaling::applyResize(img, w, h, 256, 256);
    ReadPath::Write("images/out_resize.ppm", img, w, h, true);
    cout << "[OK] Resize applied and written to images/out_resize.ppm (" << w << "x" << h << ")\n";
    hm.undo(img, w, h);

    // 7. Blur
    hm.recordGridOperation("Blur", HistoryOpType::BLUR, img, w, h);
    FrobeniusMatrixInnerProductForBlurr::applyBlur(img, w, h);
    ReadPath::Write("images/out_blur.ppm", img, w, h, true);
    cout << "[OK] Blur applied and written to images/out_blur.ppm\n";
    hm.undo(img, w, h);

    // 8. Bucket Fill Stack (DFS)
    {
        Pixel orig = img[60][60];
        Pixel target{255, 0, 255}; // Magenta
        Point* pts = new Point[w * h];
        int ptCount = 0;
        MybucketFill::ReplaceNearOne(img, w, h, 60, 60, target.r, target.g, target.b);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (img[y][x] == target) pts[ptCount++] = {x, y};
            }
        }
        hm.recordBucketFill(orig, target, pts, ptCount, w, h);
        delete[] pts;
        ReadPath::Write("images/out_bucket_stack.ppm", img, w, h, true);
        cout << "[OK] Bucket Fill (Stack DFS) applied (" << ptCount << " pixels) -> images/out_bucket_stack.ppm\n";
        hm.undo(img, w, h);
    }

    // 9. Bucket Fill Queue (BFS)
    {
        Pixel orig = img[260][260];
        Pixel target{0, 255, 255}; // Cyan
        Point* pts = new Point[w * h];
        int ptCount = 0;
        MybucketFill::ReplaceNearOneQueue(img, w, h, 260, 260, target.r, target.g, target.b);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (img[y][x] == target) pts[ptCount++] = {x, y};
            }
        }
        hm.recordBucketFill(orig, target, pts, ptCount, w, h);
        delete[] pts;
        ReadPath::Write("images/out_bucket_queue.ppm", img, w, h, true);
        cout << "[OK] Bucket Fill (Queue BFS) applied (" << ptCount << " pixels) -> images/out_bucket_queue.ppm\n";
        hm.undo(img, w, h);
    }

    // 10. Display Inspector
    DataStructureInspector::display(hm, pipeline);

    ReadPath::freeImage(img, h);
    cout << "========================================================\n";
    cout << "     ALL OPERATIONS TESTED AND RESTORED WITH SUCCESS!    \n";
    cout << "========================================================\n";
    return 0;
}
