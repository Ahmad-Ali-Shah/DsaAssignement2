========================================================================
     ImageLab - Phase 2 (Memory-Aware History, Scheduling & Evaluation)
             Roll Number: 25i-0817 | Section: E | Assignment 2
========================================================================

Directory Structure:
-------------------
src/              : All C++ source and header files including priorityQueueType,
                    memory-aware history, command coalescing, pipeline, benchmarks,
                    native image I/O, and Graphics 2 GUI subsystems.
  src/stack/      : Custom stack template with batch ops & removeBottom().
  src/queue/      : Custom circular queue template with batch ops.
  src/priority/   : Custom priority queue template (priorityQueueType).
  src/history/    : Memory-budget history manager with automatic bottom eviction.
  src/pipeline/   : Dual-mode scheduler (FIFO vs Priority with barrier rules).
  src/inspector/  : Data Structure Inspector displaying memory budget and wait times.
  src/Graphics 2/ : Interactive SFML GUI studio (Home, Selection, Input, Editor, VisPage, Cursor).
tests/            : Comprehensive Phase 2 automated test suite and verification runners.
images/           : Test images and before/after operation outputs.
report/           : Phase 2 report PDF.
README.txt        : Build, run, and library instructions.

Libraries Needed:
-----------------
- Standard C++17 Compiler (g++ or clang++)
- Zero STL containers used (zero vector, list, queue, stack).
- Zero enum, zero inline keywords used.
- Native C++ image loader/saver (PPM, PNG, JPG).
- SFML 2.6 (libsfml-graphics, libsfml-window, libsfml-system) for interactive Graphical User Interface, rocket cursor, and priority visualizer.

How to Build and Run (From 25i-0817_E_A2_P2 folder):
---------------------------------------------------
1. Compile the main application:
   g++ -std=c++17 -Wall -Wextra -Isrc src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o src/main

2. Run ImageLab Phase 2:
   ./src/main          # Interactive mode prompt: [1] Console Menu  [2] SFML GUI Studio
   ./src/main --gui    # Launch Graphical User Interface directly
   ./src/main --cli    # Launch Terminal / Console Menu Mode directly

3. Compile the Phase 2 test suite:
   g++ -std=c++17 -Wall -Wextra -Isrc tests/test.cpp -lsfml-graphics -lsfml-system -o tests/test

4. Run the Phase 2 test suite:
   ./tests/test

5. Compile and run the image verification runner:
   g++ -std=c++17 -Wall -Wextra -Isrc tests/verify_operations.cpp -lsfml-graphics -lsfml-system -o tests/verify_operations
   ./tests/verify_operations

Key Architectural Namespaces:
-----------------------------
- stackType           : Template LIFO stack with removeBottom() and batch ops
- queueType           : Template circular queue with batch ops
- priorityQueueType   : Template priority queue (Section 5 Malik interface)
- ReadPath            : Pure pointer-based PPM and image reading/writing
- HistoryManager      : Memory-budget granular history (compact inverse records)
- ProcessingPipeline  : Priority-aware scheduler enforcing Save/Export barrier
- GraphicsCursor      : Custom animated rocket ship cursor (ship.png)
- EditorPage          : Main editor GUI, canvas rendering, ribbon banner
- VisPage             : Dual-stack transfer animation & circular queue visualizer

Checklist Verification:
-----------------------
- Memory-aware history works within configurable budget (e.g., 5 MB / 50 MB)
  and discards oldest records using stackType::removeBottom().
- Command coalescing merges consecutive brightness operations, retaining clipping correctness.
- Priority queue enforces the Finalization Barrier Rule (Save/Export at Priority 4).
- Batched operations (pushBatch, popBatch, addQueueBatch, deleteQueueBatch) outperform single ops.
- All Phase 2 test cases from Section 7.7 pass completely.
