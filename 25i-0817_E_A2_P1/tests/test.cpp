#include <iostream>
#include <string>
#include <cassert>
#include "../src/image.h"
#include "../src/stack.h"
#include "../src/CircularQueue.h"
#include "../src/coreImageFunctions/bucketFill_StructBased.h"
#include "../src/coreImageFunctions/bucketFill_QueueBased.h"
#include "../src/history/history.h"
#include "../src/pipeline/pipeline.h"

using namespace std;

void assertTest(const string& testName, bool condition) {
    if (condition) {
        cout << "  [PASS] " << testName << "\n";
    } else {
        cout << "  [FAIL] " << testName << "\n";
    }
}

Pixel** createTestGrid(int w, int h, Pixel fill) {
    Pixel** grid = new Pixel*[h];
    for (int y = 0; y < h; y++) {
        grid[y] = new Pixel[w];
        for (int x = 0; x < w; x++) {
            grid[y][x] = fill;
        }
    }
    return grid;
}

void freeTestGrid(Pixel** grid, int h) {
    if (!grid) return;
    for (int y = 0; y < h; y++) {
        delete[] grid[y];
    }
    delete[] grid;
}

bool areImagesEqual(Pixel** a, Pixel** b, int w, int h) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (a[y][x] != b[y][x]) return false;
        }
    }
    return true;
}

void testUndoRedo() {
    cout << "\n========================================================\n";
    cout << "           TEST SUITE 1: UNDO AND REDO (SECTION 6.3)    \n";
    cout << "========================================================\n";

    HistoryManager hist(10);
    int w = 5, h = 5;
    Pixel white(255, 255, 255);
    Pixel red(255, 0, 0);
    Pixel blue(0, 0, 255);

    Pixel** img = createTestGrid(w, h, white);

    // Initial state: white
    hist.recordAction("Initial", img, w, h);

    // Action 1: fill red
    img[0][0] = red;
    hist.recordAction("Paint Red", img, w, h);

    // Action 2: fill blue
    img[0][0] = blue;
    hist.recordAction("Paint Blue", img, w, h);

    // Test Several Undos
    bool undo1 = hist.undo(img, w, h);
    bool checkUndo1 = undo1 && (img[0][0] == red);
    assertTest("Undo 1 restores previous action", checkUndo1);

    bool undo2 = hist.undo(img, w, h);
    bool checkUndo2 = undo2 && (img[0][0] == white);
    assertTest("Undo 2 restores original state", checkUndo2);

    // Test Several Redos
    bool redo1 = hist.redo(img, w, h);
    bool checkRedo1 = redo1 && (img[0][0] == red);
    assertTest("Redo 1 reapplies action", checkRedo1);

    bool redo2 = hist.redo(img, w, h);
    bool checkRedo2 = redo2 && (img[0][0] == blue);
    assertTest("Redo 2 reapplies latest action", checkRedo2);

    // Test new action after undo clears redo stack
    hist.undo(img, w, h); // back to red
    img[1][1] = Pixel(0, 255, 0); // new action: green
    hist.recordAction("Paint Green", img, w, h);

    bool checkRedoCleared = !hist.canRedo() && (hist.getRedoSize() == 0);
    assertTest("New action performed after undo clears Redo stack", checkRedoCleared);

    freeTestGrid(img, h);
}

void testBucketFill() {
    cout << "\n========================================================\n";
    cout << "           TEST SUITE 2: BUCKET FILL (SECTION 6.6)      \n";
    cout << "========================================================\n";

    int w = 20, h = 20;
    Pixel white(255, 255, 255);
    Pixel black(0, 0, 0);
    Pixel red(255, 0, 0);

    // Case 1: Single-pixel region
    Pixel** imgSingle = createTestGrid(3, 3, black);
    imgSingle[1][1] = white;
    MybucketFill::ReplaceNearOneQueue(imgSingle, 3, 3, 1, 1, 255, 0, 0);
    bool checkSingle = (imgSingle[1][1] == red) && (imgSingle[0][0] == black);
    assertTest("Bucket fill: Single-pixel region", checkSingle);
    freeTestGrid(imgSingle, 3);

    // Case 2: Whole image fill
    Pixel** imgWhole = createTestGrid(10, 10, white);
    MybucketFill::ReplaceNearOneQueue(imgWhole, 10, 10, 0, 0, 0, 255, 0);
    bool checkWhole = true;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (imgWhole[y][x] != Pixel(0, 255, 0)) checkWhole = false;
        }
    }
    assertTest("Bucket fill: Whole image fill", checkWhole);
    freeTestGrid(imgWhole, 10);

    // Case 3: Region touching image border
    Pixel** imgBorder = createTestGrid(10, 10, white);
    for (int y = 0; y < 10; y++) imgBorder[y][5] = black; // vertical wall
    MybucketFill::ReplaceNearOneQueue(imgBorder, 10, 10, 0, 0, 255, 0, 0); // fill left half
    bool checkBorder = (imgBorder[0][0] == red) && (imgBorder[0][4] == red) && (imgBorder[0][5] == black) && (imgBorder[0][6] == white);
    assertTest("Bucket fill: Region touching image border", checkBorder);
    freeTestGrid(imgBorder, 10);

    // Case 4: Stack-based vs Queue-based fills produce IDENTICAL output
    Pixel** imgStack = createTestGrid(w, h, white);
    Pixel** imgQueue = createTestGrid(w, h, white);

    // Make an irregular region
    for (int i = 3; i < 17; i++) {
        imgStack[i][10] = black;
        imgQueue[i][10] = black;
    }
    for (int j = 5; j < 15; j++) {
        imgStack[10][j] = black;
        imgQueue[10][j] = black;
    }

    MybucketFill::ReplaceNearOne(imgStack, w, h, 0, 0, 255, 0, 0);
    MybucketFill::ReplaceNearOneQueue(imgQueue, w, h, 0, 0, 255, 0, 0);

    bool checkIdentical = areImagesEqual(imgStack, imgQueue, w, h);
    assertTest("Stack-based and Queue-based fills give identical output", checkIdentical);

    // Case 5: Same color guard
    MybucketFill::ReplaceNearOneQueue(imgQueue, w, h, 0, 0, 255, 0, 0);
    assertTest("Same-color fill finishes without looping forever", true);

    freeTestGrid(imgStack, h);
    freeTestGrid(imgQueue, h);
}

void testPipelineQueue() {
    cout << "\n========================================================\n";
    cout << "           TEST SUITE 3: PIPELINE QUEUE (SECTION 6.5)   \n";
    cout << "========================================================\n";

    ProcessingPipeline pipeline(3);
    Job j1(1, JobType::BLUR, "Blur 1");
    Job j2(2, JobType::BLUR, "Blur 2");
    Job j3(3, JobType::BLUR, "Blur 3");
    Job j4(4, JobType::BLUR, "Blur 4");

    bool add1 = pipeline.addJob(j1);
    bool add2 = pipeline.addJob(j2);
    bool add3 = pipeline.addJob(j3);
    bool add4 = pipeline.addJob(j4); // Should be rejected by bounded capacity

    assertTest("Pipeline accepts jobs within capacity", add1 && add2 && add3);
    assertTest("Pipeline gracefully rejects jobs when full", !add4 && (pipeline.getCurrentQueueSize() == 3));

    // Cancel job
    bool cancelOk = pipeline.cancelJob(2);
    assertTest("Job can be cancelled without shifting queue", cancelOk);

    // Clear jobs
    pipeline.clearJobs();
    assertTest("Clear pending jobs empties queue", pipeline.isEmpty());
}

int main() {
    cout << "========================================================\n";
    cout << "  DSA ASSIGNMENT 2: PHASE 1 COMPREHENSIVE TEST SUITE    \n";
    cout << "========================================================\n";

    testUndoRedo();
    testBucketFill();
    testPipelineQueue();

    cout << "\n========================================================\n";
    cout << "             ALL PHASE 1 TESTS COMPLETED                \n";
    cout << "========================================================\n";
    return 0;
}
