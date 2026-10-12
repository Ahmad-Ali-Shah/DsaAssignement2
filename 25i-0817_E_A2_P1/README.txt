========================================================================
             ImageLab - Phase 1 (Data Structures & Core Editor)
             Roll Number: 25i-0817 | Section: E | Assignment 2
========================================================================

Directory Structure:
-------------------
src/              : All C++ source and header files for custom data structures,
                    core operations, history, pipeline, inspector, and file I/O.
  src/stack/      : Custom stack template (stackType).
  src/queue/      : Custom circular queue template (queueType).
  src/history/    : Undo/Redo history manager powered by custom stacks.
  src/pipeline/   : FIFO bounded processing pipeline (Job queue).
  src/inspector/  : Data Structure Inspector displaying sizes, ops, and memory.
  src/Graphics 1/ : Interactive SFML GUI studio (Home, Selection, Input, Editor, VisPage, Cursor).
tests/            : Comprehensive automated test suite for data structures and editor.
images/           : Test images (sample.ppm, sample.png, out_*.png).
report/           : Phase 1 report PDF.
README.txt        : Build, run, and library instructions.

Libraries Needed:
-----------------
- Standard C++17 Compiler (g++ or clang++)
- Zero STL containers used (zero vector, list, queue, stack).
- Zero enum, zero inline keywords used.
- Native C++ image loader/saver (PPM, PNG, JPG).
- SFML 2.6 (libsfml-graphics, libsfml-window, libsfml-system) for interactive Graphical User Interface, rocket cursor, and animated visualizers.

How to Build and Run (From 25i-0817_E_A2_P1 folder):
---------------------------------------------------
1. Compile the main application:
   g++ -std=c++17 -Wall -Wextra -Isrc src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o src/main

2. Run ImageLab:
   ./src/main          # Interactive console menu (Option 19 launches GUI)
   ./src/main --gui    # Launch Graphical User Interface directly

3. Compile the automated test suite:
   g++ -std=c++17 -Wall -Wextra -Isrc tests/test.cpp -lsfml-graphics -lsfml-system -o tests/test

4. Run the automated test suite:
   ./tests/test

Key Architectural Namespaces:
-----------------------------
- stackType           : Template LIFO stack (Section 5 Malik interface)
- queueType           : Template circular queue (Section 5 Malik interface)
- ReadPath            : Pure pointer-based PPM and image reading/writing
- HistoryManager      : Dual-stack undo/redo management
- ProcessingPipeline  : FIFO queue job manager with cancellation
- GraphicsCursor      : Custom animated rocket ship cursor (ship.png)
- EditorPage          : Main editor GUI, canvas rendering, ribbon banner
- VisPage             : Dual-stack transfer animation & circular queue visualizer

Checklist Verification:
-----------------------
- Project builds cleanly with zero warnings and zero errors.
- No STL containers (std::vector, std::list, std::queue, std::stack, etc.) used.
- No enum or forbidden language features used.
- Class and function names strictly adhere to Section 5 (Malik naming).
- Comprehensive test suite covers all minimum cases from Section 6.8.
- Data Structure Inspector displays all required metrics.
