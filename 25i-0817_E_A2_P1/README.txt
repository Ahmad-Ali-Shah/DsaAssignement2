========================================================================
             ImageLab - Phase 1 (Data Structures & Core Editor)
             Roll Number: 25i-0817 | Section: E | Assignment 2
========================================================================

Directory Structure:
-------------------
src/       : All C++ source and header files for custom data structures,
             core operations, history, pipeline, inspector, and file I/O.
tests/     : Comprehensive automated test suite for data structures and editor.
images/    : Test images (sample.ppm, sample.png).
report/    : Phase 1 report PDF.
README.txt : Build, run, and library instructions.

Libraries Needed:
-----------------
- Standard C++17 Compiler (g++ or clang++)
- Zero STL containers used (zero vector, list, queue, stack).
- Native C++ image loader/saver (PPM, PNG, JPG).
- SFML 2.6 (libsfml-graphics, libsfml-window, libsfml-system) for interactive Graphical User Interface & Sprite Animator.

How to Build and Run:
---------------------
1. Compile the main application (with SFML GUI):
   g++ -std=c++17 -Wall -Wextra src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o src/main

2. Run ImageLab:
   ./src/main          # Interactive console menu (Option 19 launches GUI)
   ./src/main --gui    # Launch Graphical User Interface directly

3. Compile the automated test suite:
   g++ -std=c++17 -Wall -Wextra tests/test.cpp -o tests/test

4. Run the automated test suite:
   ./tests/test

Checklist Verification:
-----------------------
- Project builds cleanly with zero warnings.
- No STL containers (std::vector, std::list, std::queue, std::stack, etc.) used.
- No enum or forbidden language features used.
- Class and function names strictly adhere to Section 5 (Malik naming).
- Comprehensive test suite covers all minimum cases from Section 6.8.
- Data Structure Inspector displays all required metrics.
