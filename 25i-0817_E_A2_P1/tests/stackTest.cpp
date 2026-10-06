#include <iostream>
#include <string>
#include "../src/stack.h"

using namespace std;


void assertCondition(const string& testName, bool condition) {
    if (condition) {
        cout << "[PASS] " << testName << "\n";
    } else {
        cout << "[FAIL] " << testName << "\n";
    }
}




// Test 1: Initial Empty State
void testInitialEmptyState() {
    cout << "\n--- Test 1: Initial Empty State ---\n";
    stackType<int> s(10);

    bool passed = (s.size() == 0) && s.isEmptyStack();
    assertCondition("Stack starts completely empty", passed);
}




// Test 2: Safe Pop and Top on Empty Stack (Underflow Protection)
void testEmptyUnderflowSafety() {
    cout << "\n--- Test 2: Empty Underflow Safety ---\n";
    stackType<int> s(10);

    // Should not crash the program
    int defaultVal = s.top();
    s.pop();

    bool passed = (s.size() == 0) && s.isEmptyStack() && (defaultVal == 0);
    assertCondition("Pop and Top on empty stack are handled safely without crash", passed);
}




// Test 3: Single Item Push, Top, and Pop
void testSingleItemPushPop() {
    cout << "\n--- Test 3: Single Item Push and Pop ---\n";
    stackType<int> s(10);

    s.push(100);
    bool checkPush = (s.size() == 1) && (!s.isEmptyStack()) && (s.top() == 100);

    s.pop();
    bool checkPop = (s.size() == 0) && s.isEmptyStack();

    assertCondition("Single element push, top peek, and pop", checkPush && checkPop);
}




// Test 4: LIFO (Last In First Out) Order Verification
void testLifoOrder() {
    cout << "\n--- Test 4: LIFO Order Verification ---\n";
    stackType<int> s(10);

    s.push(10);
    s.push(20);
    s.push(30);

    bool orderCorrect = true;
    if (s.top() != 30) orderCorrect = false;
    s.pop();

    if (s.top() != 20) orderCorrect = false;
    s.pop();

    if (s.top() != 10) orderCorrect = false;
    s.pop();

    bool finalCheck = orderCorrect && s.isEmptyStack() && (s.size() == 0);
    assertCondition("Elements pop in strict reverse (LIFO) order", finalCheck);
}




// Test 5: Dynamic Array Resizing (Exceeding Initial Capacity)
void testDynamicCapacityExpansion() {
    cout << "\n--- Test 5: Dynamic Capacity Expansion ---\n";
    // Initialize with a tiny capacity of 3
    stackType<int> s(3);

    // Push 8 elements to trigger dynamic resizing
    for (int i = 1; i <= 8; i++) {
        s.push(i * 10);
    }

    bool sizeCorrect = (s.size() == 8);
    bool topCorrect = (s.top() == 80);

    // Verify all 8 elements pop in proper order
    bool orderCorrect = true;
    for (int i = 8; i >= 1; i--) {
        if (s.top() != i * 10) {
            orderCorrect = false;
        }
        s.pop();
    }

    bool passed = sizeCorrect && topCorrect && orderCorrect && s.isEmptyStack();
    assertCondition("Stack automatically grows dynamically and preserves all elements", passed);
}




// Test 6: initializeStack() Resets Populated Stack
void testInitializeStack() {
    cout << "\n--- Test 6: Initialize Stack Reset ---\n";
    stackType<string> s(10);

    s.push("First");
    s.push("Second");
    s.push("Third");

    s.initializeStack();

    bool passed = (s.size() == 0) && s.isEmptyStack();
    assertCondition("initializeStack() completely resets populated stack to empty", passed);
}




// Test 7: Copy Constructor Deep Copy
void testCopyConstructorDeepCopy() {
    cout << "\n--- Test 7: Copy Constructor Deep Copy ---\n";
    stackType<int> original(10);
    original.push(1);
    original.push(2);
    original.push(3);

    // Invoke copy constructor
    stackType<int> copyStack(original);

    // Modify copyStack and ensure original is unaffected
    copyStack.pop();
    copyStack.push(999);

    bool originalUnchanged = (original.size() == 3) && (original.top() == 3);
    bool copyModified = (copyStack.size() == 3) && (copyStack.top() == 999);

    assertCondition("Copy constructor creates a truly independent deep copy", originalUnchanged && copyModified);
}




// Test 8: Overloaded Assignment Operator (=) Deep Copy
void testAssignmentOperatorDeepCopy() {
    cout << "\n--- Test 8: Assignment Operator Deep Copy ---\n";
    stackType<int> original(10);
    original.push(50);
    original.push(60);

    stackType<int> assignedStack(5);
    assignedStack.push(1);

    // Assign original to assignedStack
    assignedStack = original;

    // Modify original and check assignedStack
    original.pop();

    bool assignedIntact = (assignedStack.size() == 2) && (assignedStack.top() == 60);
    bool originalUpdated = (original.size() == 1) && (original.top() == 50);

    assertCondition("Assignment operator creates an independent deep copy", assignedIntact && originalUpdated);
}




// Test 9: Read-Only Inspection (Inspector Support without Popping)
void testReadOnlyInspection() {
    cout << "\n--- Test 9: Read-Only Inspection ---\n";
    stackType<string> s(5);
    s.push("Rotate");
    s.push("Crop");
    s.push("Blur");

    bool correctGet0 = (s.getAt(0) == "Rotate");
    bool correctGet1 = (s.getAt(1) == "Crop");
    bool correctGet2 = (s.getAt(2) == "Blur");
    bool sizePreserved = (s.size() == 3);

    cout << "Inspecting stack contents (top to bottom): ";
    s.print();

    assertCondition("Read-only inspection accesses elements without popping", correctGet0 && correctGet1 && correctGet2 && sizePreserved);
}




int main() {
    cout << "====================================================\n";
    cout << "         DATA STRUCTURE TEST SUITE: stackType       \n";
    cout << "====================================================\n";

    testInitialEmptyState();
    testEmptyUnderflowSafety();
    testSingleItemPushPop();
    testLifoOrder();
    testDynamicCapacityExpansion();
    testInitializeStack();
    testCopyConstructorDeepCopy();
    testAssignmentOperatorDeepCopy();
    testReadOnlyInspection();

    cout << "\n====================================================\n";
    cout << "             ALL STACK TESTS FINISHED               \n";
    cout << "====================================================\n";

    return 0;
}
