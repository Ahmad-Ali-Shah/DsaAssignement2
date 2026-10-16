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





void testInitialEmptyState() {
    cout << "\n--- Test 1: Initial Empty State ---\n";
    queueType<int> q(5);

    bool checkEmpty = q.isEmptyQueue();
    bool checkSize = (q.size() == 0);
    bool checkCapacity = (q.capacity() == 5);

    assertCondition("Queue starts empty with correct size and capacity", checkEmpty && checkSize && checkCapacity);
}





void testEmptyUnderflowSafety() {

    cout << "\n--- Test 2: Empty Underflow Safety ---\n";

    queueType<int> q(5);

    
    q.deleteQueue();
    int frontVal = q.front();
    int backVal = q.back();

    bool passed = q.isEmptyQueue() && (q.size() == 0) && (frontVal == 0) && (backVal == 0);

    assertCondition("deleteQueue, front, and back on empty queue handled safely", passed);

}





void testSingleItemAddDelete() {
    
    cout << "\n--- Test 3: Single Item Add and Delete ---\n";
    queueType<int> q(5);

    q.addQueue(99);
    bool checkAdd = (!q.isEmptyQueue()) && (q.size() == 1) && (q.front() == 99) && (q.back() == 99);

    q.deleteQueue();
    bool checkDelete = q.isEmptyQueue() && (q.size() == 0);

    assertCondition("Single item add, front/back check, and delete", checkAdd && checkDelete);
}





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





void testFullQueueBoundedRejection() {
    cout << "\n--- Test 5: Full Queue Bounded Rejection ---\n";
    queueType<int> q(3);

    q.addQueue(1);
    q.addQueue(2);
    q.addQueue(3);

    bool checkFull = q.isFullQueue() && (q.size() == 3);

    
    q.addQueue(999);
    bool stillIntact = (q.size() == 3) && (q.front() == 1) && (q.back() == 3);

    assertCondition("Full queue detects capacity and rejects overflow safely", checkFull && stillIntact);
}





void testCircularWrapAround() {
    cout << "\n--- Test 6: Circular Wrap-Around ---\n";
    
    queueType<int> q(4);

    
    q.addQueue(10);
    q.addQueue(20);
    q.addQueue(30);
    q.addQueue(40);

    
    q.deleteQueue();
    q.deleteQueue();

    
    q.addQueue(50);
    q.addQueue(60);

    bool checkFullAfterWrap = q.isFullQueue() && (q.size() == 4);
    bool checkFront = (q.front() == 30);
    bool checkBack = (q.back() == 60);

    
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





void testDrainAndReAdd() {
    cout << "\n--- Test 7: Complete Drain and Re-add ---\n";
    queueType<int> q(3);

    q.addQueue(100);
    q.addQueue(200);

    
    q.deleteQueue();
    q.deleteQueue();

    bool checkReset = q.isEmptyQueue() && (q.size() == 0);

    
    q.addQueue(555);
    bool checkNewAdd = (!q.isEmptyQueue()) && (q.size() == 1) && (q.front() == 555) && (q.back() == 555);

    assertCondition("Queue correctly resets to empty state and accepts new elements", checkReset && checkNewAdd);
}





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





void testCopyConstructorDeepCopy() {
    cout << "\n--- Test 9: Copy Constructor Deep Copy ---\n";
    queueType<int> original(5);
    original.addQueue(10);
    original.addQueue(20);
    original.addQueue(30);

    
    queueType<int> copyQueue(original);

    
    copyQueue.deleteQueue();
    copyQueue.addQueue(999);

    bool originalUnchanged = (original.size() == 3) && (original.front() == 10) && (original.back() == 30);
    bool copyModified = (copyQueue.size() == 3) && (copyQueue.front() == 20) && (copyQueue.back() == 999);

    assertCondition("Copy constructor creates a truly independent deep copy", originalUnchanged && copyModified);
}





void testAssignmentOperatorDeepCopy() {
    cout << "\n--- Test 10: Assignment Operator Deep Copy ---\n";
    queueType<int> original(5);
    original.addQueue(77);
    original.addQueue(88);

    queueType<int> assignedQueue(3);
    assignedQueue.addQueue(1);

    assignedQueue = original;

    
    original.deleteQueue();

    bool assignedIntact = (assignedQueue.size() == 2) && (assignedQueue.front() == 77) && (assignedQueue.back() == 88);
    bool originalUpdated = (original.size() == 1) && (original.front() == 88);

    assertCondition("Assignment operator creates an independent deep copy", assignedIntact && originalUpdated);
}





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
