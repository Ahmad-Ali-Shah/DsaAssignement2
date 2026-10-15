#include <iostream>
#include <string>
#include "../src/circularQueue.h"

using namespace std;


void assertCondition(const string& testName, bool condition) {
    if (condition) {
        cout << "[PASS] " << testName << "\n";
    } else {
        cout << "[FAIL] " << testName << "\n";
    }
}




// Test 1: Initial Empty State and Capacity Check
void testInitialEmptyState() {
    cout << "\n--- Test 1: Initial Empty State ---\n";
    queueType<int> q(5);

    bool checkEmpty = q.isEmptyQueue();
    bool checkSize = (q.size() == 0);
    bool checkCapacity = (q.capacity() == 5);

    assertCondition("Queue starts empty with correct size and capacity", checkEmpty && checkSize && checkCapacity);
}




// Test 2: Safe Underflow on Empty Queue (No crash on delete, front, back)
void testEmptyUnderflowSafety() {
    cout << "\n--- Test 2: Empty Underflow Safety ---\n";
    queueType<int> q(5);

    // Call delete and peeks on empty queue
    q.deleteQueue();
    int frontVal = q.front();
    int backVal = q.back();

    bool passed = q.isEmptyQueue() && (q.size() == 0) && (frontVal == 0) && (backVal == 0);
    assertCondition("deleteQueue, front, and back on empty queue handled safely", passed);
}




// Test 3: Single Item Add, Peek, and Delete
void testSingleItemAddDelete() {
    cout << "\n--- Test 3: Single Item Add and Delete ---\n";
    queueType<int> q(5);

    q.addQueue(99);
    bool checkAdd = (!q.isEmptyQueue()) && (q.size() == 1) && (q.front() == 99) && (q.back() == 99);

    q.deleteQueue();
    bool checkDelete = q.isEmptyQueue() && (q.size() == 0);

    assertCondition("Single item add, front/back check, and delete", checkAdd && checkDelete);
}




// Test 4: Strict FIFO (First In First Out) Order Verification
void testFifoOrder() {
    cout << "\n--- Test 4: FIFO Order Verification ---\n";
    queueType<string> q(5);

    q.addQueue("TaskA");
    q.addQueue("TaskB");
    q.addQueue("TaskC");

    bool checkFrontA = (q.front() == "TaskA") && (q.back() == "TaskC");
    q.deleteQueue();

    bool checkFrontB = (q.front() == "TaskB") && (q.back() == "TaskC");
    q.deleteQueue();

    bool checkFrontC = (q.front() == "TaskC") && (q.back() == "TaskC");
    q.deleteQueue();

    bool checkEmpty = q.isEmptyQueue() && (q.size() == 0);

    assertCondition("Jobs process in strict FIFO arrival order", checkFrontA && checkFrontB && checkFrontC && checkEmpty);
}




// Test 5: Full Queue Detection and Bounded Rejection
void testFullQueueBoundedRejection() {
    cout << "\n--- Test 5: Full Queue Bounded Rejection ---\n";
    queueType<int> q(3);

    q.addQueue(1);
    q.addQueue(2);
    q.addQueue(3);

    bool checkFull = q.isFullQueue() && (q.size() == 3);

    // Attempting 4th addition should be rejected gracefully
    q.addQueue(999);
    bool stillIntact = (q.size() == 3) && (q.front() == 1) && (q.back() == 3);

    assertCondition("Full queue detects capacity and rejects overflow safely", checkFull && stillIntact);
}




// Test 6: Circular Wrap-Around (Dry-Run Scenario: add, delete, wrap rear to index 0)
void testCircularWrapAround() {
    cout << "\n--- Test 6: Circular Wrap-Around ---\n";
    // Capacity of 4
    queueType<int> q(4);

    // Fill completely: [10, 20, 30, 40]
    q.addQueue(10);
    q.addQueue(20);
    q.addQueue(30);
    q.addQueue(40);

    // Delete 2 items: 10 and 20 are removed, front moves to index 2
    q.deleteQueue();
    q.deleteQueue();

    // Now queue has 2 elements [30, 40], rear wraps to index 0 and 1
    q.addQueue(50);
    q.addQueue(60);

    bool checkFullAfterWrap = q.isFullQueue() && (q.size() == 4);
    bool checkFront = (q.front() == 30);
    bool checkBack = (q.back() == 60);

    // Drain all 4 items to ensure wrap-around maintained correct order
    bool orderCorrect = true;
    int expected[] = {30, 40, 50, 60};
    for (int i = 0; i < 4; i++) {
        if (q.front() != expected[i]) {
            orderCorrect = false;
        }
        q.deleteQueue();
    }

    assertCondition("Circular wrap-around handles buffer wrap and preserves order", checkFullAfterWrap && checkFront && checkBack && orderCorrect && q.isEmptyQueue());
}




// Test 7: Complete Drain and Re-add from Empty (-1 Reset)
void testDrainAndReAdd() {
    cout << "\n--- Test 7: Complete Drain and Re-add ---\n";
    queueType<int> q(3);

    q.addQueue(100);
    q.addQueue(200);

    // Drain both
    q.deleteQueue();
    q.deleteQueue();

    bool checkReset = q.isEmptyQueue() && (q.size() == 0);

    // Add again from fresh reset state
    q.addQueue(555);
    bool checkNewAdd = (!q.isEmptyQueue()) && (q.size() == 1) && (q.front() == 555) && (q.back() == 555);

    assertCondition("Queue correctly resets to empty state and accepts new elements", checkReset && checkNewAdd);
}




// Test 8: initializeQueue() Resets Populated Queue
void testInitializeQueue() {
    cout << "\n--- Test 8: Initialize Queue Reset ---\n";
    queueType<int> q(5);

    q.addQueue(1);
    q.addQueue(2);
    q.addQueue(3);

    q.initializeQueue();

    bool passed = q.isEmptyQueue() && (q.size() == 0);
    assertCondition("initializeQueue() resets populated queue completely", passed);
}




// Test 9: Copy Constructor Deep Copy
void testCopyConstructorDeepCopy() {
    cout << "\n--- Test 9: Copy Constructor Deep Copy ---\n";
    queueType<int> original(5);
    original.addQueue(10);
    original.addQueue(20);
    original.addQueue(30);

    // Copy construct
    queueType<int> copyQueue(original);

    // Delete from copyQueue and ensure original remains unaffected
    copyQueue.deleteQueue();
    copyQueue.addQueue(999);

    bool originalUnchanged = (original.size() == 3) && (original.front() == 10) && (original.back() == 30);
    bool copyModified = (copyQueue.size() == 3) && (copyQueue.front() == 20) && (copyQueue.back() == 999);

    assertCondition("Copy constructor creates a truly independent deep copy", originalUnchanged && copyModified);
}




// Test 10: Overloaded Assignment Operator (=) Deep Copy
void testAssignmentOperatorDeepCopy() {
    cout << "\n--- Test 10: Assignment Operator Deep Copy ---\n";
    queueType<int> original(5);
    original.addQueue(77);
    original.addQueue(88);

    queueType<int> assignedQueue(3);
    assignedQueue.addQueue(1);

    assignedQueue = original;

    // Modify original
    original.deleteQueue();

    bool assignedIntact = (assignedQueue.size() == 2) && (assignedQueue.front() == 77) && (assignedQueue.back() == 88);
    bool originalUpdated = (original.size() == 1) && (original.front() == 88);

    assertCondition("Assignment operator creates an independent deep copy", assignedIntact && originalUpdated);
}




// Test 11: Read-Only Inspection (Pending Job List Support without Dequeuing)
void testReadOnlyInspection() {
    cout << "\n--- Test 11: Read-Only Inspection ---\n";
    queueType<string> q(5);
    q.addQueue("Resize");
    q.addQueue("Blur");
    q.addQueue("Export");

    bool correctGet0 = (q.getAt(0) == "Resize");
    bool correctGet1 = (q.getAt(1) == "Blur");
    bool correctGet2 = (q.getAt(2) == "Export");
    bool countPreserved = (q.size() == 3);

    cout << "Inspecting pending jobs (front to rear): ";
    q.print();

    assertCondition("Read-only inspection visits elements without dequeuing", correctGet0 && correctGet1 && correctGet2 && countPreserved);
}




int main() {
    cout << "====================================================\n";
    cout << "        DATA STRUCTURE TEST SUITE: queueType        \n";
    cout << "====================================================\n";

    testInitialEmptyState();
    testEmptyUnderflowSafety();
    testSingleItemAddDelete();
    testFifoOrder();
    testFullQueueBoundedRejection();
    testCircularWrapAround();
    testDrainAndReAdd();
    testInitializeQueue();
    testCopyConstructorDeepCopy();
    testAssignmentOperatorDeepCopy();
    testReadOnlyInspection();

    cout << "\n====================================================\n";
    cout << "             ALL QUEUE TESTS FINISHED               \n";
    cout << "====================================================\n";

    return 0;
}
