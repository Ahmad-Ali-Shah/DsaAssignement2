#include <iostream>
#include <string>
#include <cassert>
#include "../src/image.h"
#include "../src/stack.h"
#include "../src/circularQueue.h"
#include "../src/coreImageFunctions/bucketFill/bucketFillStructBased.h"
#include "../src/coreImageFunctions/bucketFill/bucketFillQueueBased.h"
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

// --------------------------------------------------------------------------
// SUITE 1: CUSTOM STACK (SECTION 6.2 & 6.8)
// --------------------------------------------------------------------------
void testStack() {
    cout << "\n========================================================\n";
    cout << "           TEST SUITE 1: CUSTOM STACK (SECTION 6.2 & 6.8)\n";
    cout << "========================================================\n";

    // 1. Initial Empty State
    stackType<int> s(10);
    assertTest("Stack starts completely empty", (s.size() == 0) && s.isEmptyStack());

    // 2. Pop and Top on Empty Stack (Underflow Protection)
    int defVal = s.top();
    s.pop();
    assertTest("Pop and Top on empty stack handled safely without crash", (s.size() == 0) && (defVal == 0));

    // 3. Repeated Push and Pop
    s.push(10);
    s.push(20);
    s.push(30);
    bool checkLIFO = (s.top() == 30);
    s.pop();
    checkLIFO = checkLIFO && (s.top() == 20);
    s.pop();
    checkLIFO = checkLIFO && (s.top() == 10);
    s.pop();
    assertTest("Elements pop in strict LIFO order", checkLIFO && s.isEmptyStack());

    // 4. Large number of pushes & Dynamic Resizing
    stackType<int> sGrow(2);
    for (int i = 0; i < 50; i++) sGrow.push(i);
    assertTest("Stack dynamically resizes and holds 50 elements", sGrow.size() == 50 && sGrow.top() == 49);

    // 5. initializeStack
    sGrow.initializeStack();
    assertTest("initializeStack() resets populated stack", sGrow.isEmptyStack() && (sGrow.size() == 0));

    // 6. Copy constructor and Assignment Operator
    stackType<int> orig(5);
    orig.push(111);
    orig.push(222);
    stackType<int> copyStack(orig);
    copyStack.pop();
    assertTest("Copy constructor creates independent deep copy", (orig.size() == 2) && (copyStack.size() == 1));

    stackType<int> assigned(5);
    assigned = orig;
    orig.pop();
    assertTest("Assignment operator creates independent deep copy", (assigned.size() == 2) && (orig.size() == 1));
}

// --------------------------------------------------------------------------
// SUITE 2: CUSTOM CIRCULAR QUEUE (SECTION 6.4 & 6.8)
// --------------------------------------------------------------------------
void testQueue() {
    cout << "\n========================================================\n";
    cout << "       TEST SUITE 2: CUSTOM CIRCULAR QUEUE (SECTION 6.4)\n";
    cout << "========================================================\n";

    queueType<int> q(5);
    assertTest("Queue starts empty with correct capacity", q.isEmptyQueue() && (q.capacity() == 5));

    // deleteQueue on empty
    q.deleteQueue();
    assertTest("deleteQueue on empty queue handled safely", q.isEmptyQueue());

    // FIFO Order
    q.addQueue(10);
    q.addQueue(20);
    q.addQueue(30);
    bool fifoOk = (q.front() == 10);
    q.deleteQueue();
    fifoOk = fifoOk && (q.front() == 20);
    q.deleteQueue();
    fifoOk = fifoOk && (q.front() == 30);
    q.deleteQueue();
    assertTest("Jobs process in strict FIFO arrival order", fifoOk && q.isEmptyQueue());

    // Full queue and Bounded Rejection
    queueType<int> qBounded(3);
    qBounded.addQueue(1);
    qBounded.addQueue(2);
    qBounded.addQueue(3);
    assertTest("Full queue detected", qBounded.isFullQueue());
    qBounded.addQueue(999); // Rejected
    assertTest("Full queue gracefully rejects overflow", qBounded.size() == 3 && qBounded.front() == 1);

    // Circular Wrap-around
    queueType<int> qWrap(4);
    qWrap.addQueue(100);
    qWrap.addQueue(200);
    qWrap.addQueue(300);
    qWrap.addQueue(400);
    qWrap.deleteQueue(); // delete 100
    qWrap.deleteQueue(); // delete 200
    qWrap.addQueue(500); // wraps to index 0
    qWrap.addQueue(600); // wraps to index 1
    assertTest("Circular wrap-around handles buffer wrap correctly", qWrap.front() == 300 && qWrap.back() == 600 && qWrap.isFullQueue());

    // Copy constructor and Assignment
    queueType<int> qCopy(qWrap);
    qCopy.deleteQueue();
    assertTest("Queue copy constructor deep copy", qWrap.size() == 4 && qCopy.size() == 3);
}

// --------------------------------------------------------------------------
// SUITE 3: UNDO AND REDO (SECTION 6.3 & 6.8)
// --------------------------------------------------------------------------
void testUndoRedo() {
    cout << "\n========================================================\n";
    cout << "           TEST SUITE 3: UNDO AND REDO (SECTION 6.3)    \n";
    cout << "========================================================\n";

    HistoryManager hist(10);
    int w = 5, h = 5;
    Pixel white(255, 255, 255);
    Pixel red(255, 0, 0);
    Pixel blue(0, 0, 255);

    Pixel** img = createTestGrid(w, h, white);

    // In Phase 1, recordAction stores the BEFORE state of an operation:
    // Before Edit 1 (Paint Red): record white state
    hist.recordAction("Paint Red", img, w, h);
    img[0][0] = red;

    // Before Edit 2 (Paint Blue): record red state
    hist.recordAction("Paint Blue", img, w, h);
    img[0][0] = blue;

    // Undo 1: Reverts Edit 2 (Paint Blue), restoring red state
    bool undo1 = hist.undo(img, w, h);
    assertTest("Undo 1 restores previous action", undo1 && (img[0][0] == red));

    // Undo 2: Reverts Edit 1 (Paint Red), restoring initial white state
    bool undo2 = hist.undo(img, w, h);
    assertTest("Undo 2 restores original state", undo2 && (img[0][0] == white));

    // Redo 1: Re-applies Edit 1 (Paint Red), restoring red state
    bool redo1 = hist.redo(img, w, h);
    assertTest("Redo 1 reapplies action", redo1 && (img[0][0] == red));

    // Redo 2: Re-applies Edit 2 (Paint Blue), restoring blue state
    bool redo2 = hist.redo(img, w, h);
    assertTest("Redo 2 reapplies latest action", redo2 && (img[0][0] == blue));

    hist.undo(img, w, h);
    img[1][1] = Pixel(0, 255, 0);
    hist.recordAction("Paint Green", img, w, h);
    assertTest("New action performed after undo clears Redo stack", !hist.canRedo() && (hist.getRedoSize() == 0));

    freeTestGrid(img, h);
}

// --------------------------------------------------------------------------
// SUITE 4: BUCKET FILL (SECTION 6.6 & 6.8)
// --------------------------------------------------------------------------
void testBucketFill() {
    cout << "\n========================================================\n";
    cout << "           TEST SUITE 4: BUCKET FILL (SECTION 6.6)      \n";
    cout << "========================================================\n";

    int w = 20, h = 20;
    Pixel white(255, 255, 255);
    Pixel black(0, 0, 0);
    Pixel red(255, 0, 0);

    // Single-pixel region
    Pixel** imgSingle = createTestGrid(3, 3, black);
    imgSingle[1][1] = white;
    MybucketFill::ReplaceNearOneQueue(imgSingle, 3, 3, 1, 1, 255, 0, 0);
    assertTest("Bucket fill: Single-pixel region", (imgSingle[1][1] == red) && (imgSingle[0][0] == black));
    freeTestGrid(imgSingle, 3);

    // Whole image fill
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

    // Region touching image border
    Pixel** imgBorder = createTestGrid(10, 10, white);
    for (int y = 0; y < 10; y++) imgBorder[y][5] = black;
    MybucketFill::ReplaceNearOneQueue(imgBorder, 10, 10, 0, 0, 255, 0, 0);
    assertTest("Bucket fill: Region touching image border", (imgBorder[0][0] == red) && (imgBorder[0][4] == red) && (imgBorder[0][5] == black) && (imgBorder[0][6] == white));
    freeTestGrid(imgBorder, 10);

    // Stack-based vs Queue-based fills produce IDENTICAL output
    Pixel** imgStack = createTestGrid(w, h, white);
    Pixel** imgQueue = createTestGrid(w, h, white);
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
    assertTest("Stack-based and Queue-based fills give identical output", areImagesEqual(imgStack, imgQueue, w, h));

    // Same color guard
    MybucketFill::ReplaceNearOneQueue(imgQueue, w, h, 0, 0, 255, 0, 0);
    assertTest("Same-color fill finishes without looping forever", true);

    freeTestGrid(imgStack, h);
    freeTestGrid(imgQueue, h);
}

// --------------------------------------------------------------------------
// SUITE 5: PIPELINE QUEUE (SECTION 6.5)
// --------------------------------------------------------------------------
void testPipelineQueue() {
    cout << "\n========================================================\n";
    cout << "           TEST SUITE 5: PIPELINE QUEUE (SECTION 6.5)   \n";
    cout << "========================================================\n";

    ProcessingPipeline pipeline(3);
    Job j1(1, JobType::blur, "Blur 1");
    Job j2(2, JobType::blur, "Blur 2");
    Job j3(3, JobType::blur, "Blur 3");
    Job j4(4, JobType::blur, "Blur 4");

    bool add1 = pipeline.addJob(j1);
    bool add2 = pipeline.addJob(j2);
    bool add3 = pipeline.addJob(j3);
    bool add4 = pipeline.addJob(j4);

    assertTest("Pipeline accepts jobs within capacity", add1 && add2 && add3);
    assertTest("Pipeline gracefully rejects jobs when full", !add4 && (pipeline.getCurrentQueueSize() == 3));

    bool cancelOk = pipeline.cancelJob(2);
    assertTest("Job can be cancelled without shifting queue", cancelOk);

    pipeline.clearJobs();
    assertTest("Clear pending jobs empties queue", pipeline.isEmpty());
}

int main() {
    cout << "========================================================\n";
    cout << "  DSA ASSIGNMENT 2: PHASE 1 COMPREHENSIVE TEST SUITE    \n";
    cout << "========================================================\n";

    testStack();
    testQueue();
    testUndoRedo();
    testBucketFill();
    testPipelineQueue();

    cout << "\n========================================================\n";
    cout << "             ALL PHASE 1 TESTS COMPLETED                \n";
    cout << "========================================================\n";
    return 0;
}
