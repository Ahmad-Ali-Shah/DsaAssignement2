#include <iostream>

// Forward declarations of test runners
void runStackTests();
void runQueueTests();

int main() {
    std::cout << "========================================================\n";
    std::cout << "  DSA ASSIGNMENT 2: COMPREHENSIVE DATA STRUCTURE TESTS  \n";
    std::cout << "========================================================\n\n";

    std::cout << "To run the individual test suites:\n";
    std::cout << "  1. Stack Tests:        g++ tests/stackTest.cpp -o tests/stackTest && ./tests/stackTest\n";
    std::cout << "  2. Circular Queue Tests: g++ tests/queueTest.cpp -o tests/queueTest && ./tests/queueTest\n\n";

    return 0;
}
