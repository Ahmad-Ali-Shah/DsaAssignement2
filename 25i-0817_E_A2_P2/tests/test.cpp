#include <iostream>
#include <cassert>
#include <string>
#include "../src/image.h"
#include "../src/stack.h"
#include "../src/circularQueue.h"
#include "../src/priorityQueue.h"
#include "../src/history/history.h"
#include "../src/pipeline/job.h"
#include "../src/pipeline/pipeline.h"
#include "../src/benchmarks.h"

using namespace std;

// Helper to create test image
Pixel** createTestGrid(int w, int h, Pixel fill) {
    Pixel** g = new Pixel*[h];
    for (int y = 0; y < h; y++) {
        g[y] = new Pixel[w];
        for (int x = 0; x < w; x++) {
            g[y][x] = fill;
        }
    }
    return g;
}

void freeTestGrid(Pixel** g, int h) {
    if (!g) return;
    for (int y = 0; y < h; y++) delete[] g[y];
    delete[] g;
}

bool gridsEqual(Pixel** a, Pixel** b, int w, int h) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (a[y][x] != b[y][x]) return false;
        }
    }
    return true;
}

// --------------------------------------------------------------------------
// SUITE 1: PRIORITY QUEUE & SCHEDULER (SECTION 7.3 & 7.7)
// --------------------------------------------------------------------------
void testPriorityQueue() {
    cout << "--- TEST SUITE 1: PRIORITY QUEUE & SCHEDULER ---\n";
    priorityQueueType<Job> pq(20);

    // 1. Same-priority jobs served in arrival order (FIFO tie-breaking)
    pq.addQueue(Job(1, JobType::blur, "Blur A", 2, 10));
    pq.addQueue(Job(2, JobType::blur, "Blur B", 2, 20));
    pq.addQueue(Job(3, JobType::blur, "Blur C", 2, 30));

    assert(pq.front().id == 1); pq.deleteQueue();
    assert(pq.front().id == 2); pq.deleteQueue();
    assert(pq.front().id == 3); pq.deleteQueue();
    cout << "  [PASS] Same-priority jobs served in arrival order (FIFO tie handling)\n";

    // 2. Mixed priorities
    pq.addQueue(Job(4, JobType::resize, "Resize", 3, 1));
    pq.addQueue(Job(5, JobType::undoRedo, "Undo", 1, 2));
    pq.addQueue(Job(6, JobType::blur, "Blur", 2, 3));

    assert(pq.front().id == 5); pq.deleteQueue(); // Pri 1
    assert(pq.front().id == 6); pq.deleteQueue(); // Pri 2
    assert(pq.front().id == 4); pq.deleteQueue(); // Pri 3
    cout << "  [PASS] Mixed priorities correctly scheduled by priority rank\n";

    // 3. Finalization barrier rule:
    // Submitted: Resize(3) Blur(2) Export(4) Blur(2) Undo(1)
    // Expected:  Blur(2), Resize(3), Export(4), Undo(1), Blur(2)
    pq.addQueue(Job(10, JobType::resize, "Resize(3)", 3, 1));
    pq.addQueue(Job(20, JobType::blur, "Blur(2)", 2, 2));
    pq.addQueue(Job(30, JobType::exportImage, "Export(4) [Barrier]", 4, 3));
    pq.addQueue(Job(40, JobType::blur, "Blur(2)-post", 2, 4));
    pq.addQueue(Job(50, JobType::undoRedo, "Undo(1)-post", 1, 5));

    assert(pq.front().id == 20); pq.deleteQueue(); // Blur(2)
    assert(pq.front().id == 10); pq.deleteQueue(); // Resize(3)
    assert(pq.front().id == 30); pq.deleteQueue(); // Export(4) barrier runs once prior jobs finish
    assert(pq.front().id == 50); pq.deleteQueue(); // Undo(1) cannot overtake Export before Export ran
    assert(pq.front().id == 40); pq.deleteQueue(); // Blur(2)-post
    cout << "  [PASS] Finalization barrier rule enforced (jobs cannot overtake barrier)\n";
}

// --------------------------------------------------------------------------
// SUITE 2: MEMORY-AWARE HISTORY & EVICTION (SECTION 7.1 & 7.7)
// --------------------------------------------------------------------------
void testMemoryAwareHistory() {
    cout << "\n--- TEST SUITE 2: MEMORY-AWARE HISTORY & EVICTION ---\n";
    HistoryManager hm(2048);
    int w = 10, h = 10;
    Pixel** img = createTestGrid(w, h, {100, 100, 100});

    for (int i = 0; i < 15; i++) {
        hm.recordGridOperation("Grayscale " + to_string(i), HistoryOpType::grayscale, img, w, h);
    }

    assert(hm.getDiscardedRecordsCount() > 0);
    cout << "  [PASS] Memory budget reached and oldest records evicted via removeBottom()\n";
    cout << "         (Total evicted: " << hm.getDiscardedRecordsCount() << " records)\n";

    bool undoOk = hm.undo(img, w, h);
    assert(undoOk);
    cout << "  [PASS] Undo after cleanup operates safely without memory fault\n";

    int testW = 4, testH = 4;
    Pixel** origImg = createTestGrid(testW, testH, {50, 100, 150});
    Pixel** currImg = createTestGrid(testW, testH, {50, 100, 150});

    hm.recordRotate(90, testW, testH);
    currImg = rotateObject::applyRotate(currImg, testW, testH, 90);
    hm.undo(currImg, testW, testH);
    assert(gridsEqual(origImg, currImg, 4, 4));
    cout << "  [PASS] Rotate undo restores exact previous image\n";

    hm.recordFlip(true, testW, testH);
    flipAxis::applyFlipHorizontal(currImg, testW, testH);
    hm.undo(currImg, testW, testH);
    assert(gridsEqual(origImg, currImg, 4, 4));
    cout << "  [PASS] Flip undo restores exact previous image\n";

    Pixel fillTarget{200, 200, 200};
    Point pts[4] = {{0,0}, {0,1}, {1,0}, {1,1}};
    for (int i = 0; i < 4; i++) currImg[pts[i].coordinatesY][pts[i].coordinatesX] = fillTarget;
    hm.recordBucketFill({50, 100, 150}, fillTarget, pts, 4, testW, testH);
    hm.undo(currImg, testW, testH);
    assert(gridsEqual(origImg, currImg, 4, 4));
    cout << "  [PASS] Bucket fill undo restores exact previous image\n";

    freeTestGrid(origImg, 4);
    freeTestGrid(currImg, testH);
    freeTestGrid(img, h);
}

// --------------------------------------------------------------------------
// SUITE 3: COMMAND COALESCING (SECTION 7.2 & 7.7)
// --------------------------------------------------------------------------
void testCommandCoalescing() {
    cout << "\n--- TEST SUITE 3: COMMAND COALESCING ---\n";
    HistoryManager hm(50 * 1024 * 1024);
    int w = 5, h = 5;
    Pixel** img = createTestGrid(w, h, {100, 100, 100});
    Pixel** baseline = createTestGrid(w, h, {100, 100, 100});

    hm.recordBrightness(10.0, img, w, h);
    MyBrightness::applyBrightness(img, w, h, 10.0);

    hm.recordBrightness(15.0, img, w, h);
    MyBrightness::applyBrightness(img, w, h, 15.0);

    hm.recordBrightness(-5.0, img, w, h);
    MyBrightness::applyBrightness(img, w, h, -5.0);

    assert(hm.getUndoSize() == 1);
    cout << "  [PASS] Repeated brightness operations coalesced into a single record\n";

    bool undoOk = hm.undo(img, w, h);
    assert(undoOk);
    assert(gridsEqual(img, baseline, w, h));
    assert(hm.getUndoSize() == 0);
    cout << "  [PASS] Single undo of coalesced record completely restores original image\n";

    hm.recordBrightness(10.0, img, w, h);
    hm.recordFlip(true, w, h);
    hm.recordBrightness(20.0, img, w, h);
    assert(hm.getUndoSize() == 3);
    cout << "  [PASS] Brightness separated by another operation maintains separate records\n";

    Pixel** clipImg = createTestGrid(2, 2, {200, 200, 200});
    Pixel** clipBase = createTestGrid(2, 2, {200, 200, 200});
    HistoryManager clipHm(1024 * 1024);

    clipHm.recordBrightness(100.0, clipImg, 2, 2);
    MyBrightness::applyBrightness(clipImg, 2, 2, 100.0);
    clipHm.recordBrightness(-50.0, clipImg, 2, 2);
    MyBrightness::applyBrightness(clipImg, 2, 2, -50.0);

    int clipW = 2, clipH = 2;
    clipHm.undo(clipImg, clipW, clipH);
    assert(gridsEqual(clipImg, clipBase, 2, 2));
    cout << "  [PASS] Clipping correctness preserved during coalesced brightness undo\n";

    freeTestGrid(img, h);
    freeTestGrid(baseline, h);
    freeTestGrid(clipImg, 2);
    freeTestGrid(clipBase, 2);
}

// --------------------------------------------------------------------------
// SUITE 4: BATCHED OPERATIONS (SECTION 7.4 & 7.7)
// --------------------------------------------------------------------------
void testBatchedOperations() {
    cout << "\n--- TEST SUITE 4: BATCHED OPERATIONS ---\n";
    stackType<int> st(10);
    int items[5] = {10, 20, 30, 40, 50};
    st.pushBatch(items, 5);
    assert(st.size() == 5);
    assert(st.top() == 50);

    st.popBatch(3);
    assert(st.size() == 2);
    assert(st.top() == 20);

    st.popBatch(100);
    assert(st.size() == 0);
    cout << "  [PASS] Stack pushBatch, popBatch, and popBatch with n > size\n";

    queueType<int> q(6);
    int init[4] = {1, 2, 3, 4};
    q.addQueueBatch(init, 4);
    q.deleteQueueBatch(2);

    int wrapItems[3] = {5, 6, 7};
    bool added = q.addQueueBatch(wrapItems, 3);
    assert(added);
    assert(q.size() == 5);
    assert(q.front() == 3);
    assert(q.back() == 7);
    cout << "  [PASS] Queue addQueueBatch across circular wrap-around\n";

    int overflowItems[5] = {10, 20, 30, 40, 50};
    bool rejected = !q.addQueueBatch(overflowItems, 5);
    assert(rejected);
    cout << "  [PASS] Batch larger than free space safely rejected by bounded queue\n";

    q.deleteQueueBatch(50);
    assert(q.isEmptyQueue());
    cout << "  [PASS] deleteQueueBatch with n > size empties queue safely\n";
}

// --------------------------------------------------------------------------
// SUITE 5: WORKLOAD BENCHMARK VERIFICATION (SECTION 7.3 & 7.5)
// --------------------------------------------------------------------------
void testWorkloadBenchmark() {
    cout << "\n--- TEST SUITE 5: 30-JOB BENCHMARK EXECUTION ---\n";
    WorkloadBenchmark::runBenchmarkComparison();
    cout << "  [PASS] 30-Job Workload executed in both FIFO and Priority modes\n";
}

int main() {
    cout << "=========================================================================\n";
    cout << "           RUNNING AUTOMATED TEST SUITE: PHASE 2 (SECTION 7.7)           \n";
    cout << "=========================================================================\n\n";

    testPriorityQueue();
    testMemoryAwareHistory();
    testCommandCoalescing();
    testBatchedOperations();
    testWorkloadBenchmark();

    cout << "=========================================================================\n";
    cout << "                 ALL PHASE 2 TESTS COMPLETED SUCCESSFULLY!                \n";
    cout << "=========================================================================\n";

    return 0;
}
