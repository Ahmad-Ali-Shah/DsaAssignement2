========================================================================
     ImageLab - Phase 2 (Memory-Aware History, Scheduling & Evaluation)
             Roll Number: 25i-0817 | Section: E | Assignment 2
========================================================================

Directory Structure:
-------------------
src/       : All C++ source and header files including priorityQueueType,
             memory-aware history, command coalescing, pipeline, benchmarks,
             native image I/O, and Graphics 2 GUI subsystems.
tests/     : Comprehensive Phase 2 automated test suite and verification runners.
images/    : Test images and before/after operation outputs.
report/    : Phase 2 report PDF.
README.txt : Build, run, and library instructions.

Libraries Needed:
-----------------
- Standard C++17 Compiler (g++ or clang++)
- Zero STL containers used (zero vector, list, queue, stack).
- Native C++ image loader/saver (PPM, PNG, JPG).
- SFML 2.6 (libsfml-graphics, libsfml-window, libsfml-system) for interactive Graphical User Interface & Priority Scheduler Visualizer.

How to Build and Run:
---------------------
1. Compile the main application (with SFML GUI):
   g++ -std=c++17 -Wall -Wextra src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o src/main

2. Run ImageLab Phase 2:
   ./src/main          # Interactive console menu (Option 23 launches GUI)
   ./src/main --gui    # Launch Graphical User Interface directly

3. Compile the Phase 2 test suite:
   g++ -std=c++17 -Wall -Wextra tests/test.cpp -o tests/test

4. Run the Phase 2 test suite:
   ./tests/test

5. Compile and run the operational verification runner on images:
   g++ -std=c++17 -Wall -Wextra tests/verify_operations.cpp -o tests/verify_operations
   ./tests/verify_operations

Checklist Verification:
-----------------------
- Memory-aware history works within configurable budget (e.g., 5 MB / 50 MB)
  and discards oldest records using stackType::removeBottom().
- Command coalescing merges consecutive brightness operations, retaining clipping correctness.
- Priority queue enforces the Finalization Barrier Rule (Save/Export at Priority 4).
- Batched operations (pushBatch, popBatch, addQueueBatch, deleteQueueBatch) outperform single ops.
- All Phase 2 test cases from Section 7.7 pass completely.
