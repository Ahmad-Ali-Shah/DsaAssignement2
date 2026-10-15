========================================================================
     ImageLab - Phase 2 (Memory-Aware History, Scheduling & Evaluation)
             Roll Number: 25i-0817 | Section: E | Assignment 2
========================================================================

Directory Structure (C++ Headers & Source Files):
-------------------------------------------------
25i-0817_E_A2_P2
├── src
│   ├── benchmarks.h
│   ├── CircularQueue.h
│   ├── coreImageFunctions
│   │   ├── blur
│   │   │   ├── applyBlur.h
│   │   │   └── blur.h
│   │   ├── blur.h
│   │   ├── brightness
│   │   │   ├── applyBrightness.h
│   │   │   └── brightness.h
│   │   ├── brightness.h
│   │   ├── bucketFill
│   │   │   ├── bucketFill_QueueBased.h
│   │   │   └── bucketFill_StructBased.h
│   │   ├── bucketFill.h
│   │   ├── bucketFill_QueueBased.h
│   │   ├── bucketFill_StructBased.h
│   │   ├── Crop
│   │   │   ├── applyCrop.h
│   │   │   └── Crop.h
│   │   ├── Crop.h
│   │   ├── flip
│   │   │   ├── applyFlip.h
│   │   │   └── flip.h
│   │   ├── flip.h
│   │   ├── greyScale
│   │   │   ├── applyGreyScale.h
│   │   │   └── greyScale.h
│   │   ├── greyScale.h
│   │   ├── resize
│   │   │   ├── applyResize.h
│   │   │   └── resize.h
│   │   ├── resize.h
│   │   ├── rotation
│   │   │   ├── applyRotation.h
│   │   │   └── rotation.h
│   │   └── rotation.h
│   ├── Graphics 2
│   │   ├── app
│   │   │   ├── handleToolExecution2.h
│   │   │   ├── renderApp2.h
│   │   │   ├── resolveAssetPath.h
│   │   │   └── runGraphics2.h
│   │   ├── benchmarkView
│   │   │   └── renderSchedulerComparisonTable.h
│   │   ├── canvas
│   │   │   └── createTextureFromPixels.h
│   │   ├── coalescingView
│   │   │   └── renderCoalescingBadge.h
│   │   ├── cursor
│   │   │   └── cursor.h
│   │   ├── dualFill
│   │   │   └── renderDualFillComparison.h
│   │   ├── editorPage
│   │   │   ├── editorConstants.h
│   │   │   ├── executeEditorAction.h
│   │   │   ├── loadEditorAssets.h
│   │   │   ├── renderEditorBanner.h
│   │   │   ├── renderLeftToolbar.h
│   │   │   ├── renderMiddleCanvas.h
│   │   │   ├── renderParameterModal.h
│   │   │   ├── renderRightPanel.h
│   │   │   └── runEditorPage.h
│   │   ├── homePage
│   │   │   ├── homeConstants.h
│   │   │   ├── loadAsteroidTextures.h
│   │   │   ├── loadCatTexture.h
│   │   │   ├── loadHomeFonts.h
│   │   │   ├── renderAsteroidCorner.h
│   │   │   ├── renderCatSprite.h
│   │   │   ├── renderHomePage.h
│   │   │   ├── renderHomeTitle.h
│   │   │   ├── runHomePage.h
│   │   │   └── updateCatState.h
│   │   ├── inputPage
│   │   │   ├── inputConstants.h
│   │   │   ├── loadInputAssets.h
│   │   │   ├── renderInputBackground.h
│   │   │   ├── renderInputPrompt.h
│   │   │   ├── renderLoadingScreen.h
│   │   │   ├── runInputPage.h
│   │   │   └── validateAndLoadImage.h
│   │   ├── memoryGauge
│   │   │   └── renderMemoryBudgetMeter.h
│   │   ├── scheduler
│   │   │   ├── renderBarrierIndicator.h
│   │   │   ├── renderPriorityCard.h
│   │   │   └── renderPriorityQueueBar.h
│   │   ├── selectionPage
│   │   │   ├── loadSelectionAssets.h
│   │   │   ├── renderSelectionBackground.h
│   │   │   ├── renderSelectionOptions.h
│   │   │   ├── renderSelectionPage.h
│   │   │   ├── renderSelectionTitle.h
│   │   │   ├── renderShipCursor.h
│   │   │   ├── runSelectionPage.h
│   │   │   ├── selectionConstants.h
│   │   │   └── updateShipSpeed.h
│   │   ├── theme
│   │   │   ├── drawBadge.h
│   │   │   └── drawMeter.h
│   │   ├── types
│   │   │   └── priorityConstants.h
│   │   ├── visPage
│   │   │   ├── loadVisAssets.h
│   │   │   ├── renderDataWindow.h
│   │   │   ├── renderVisControls.h
│   │   │   ├── runVisPage.h
│   │   │   ├── updateVisAnimation.h
│   │   │   └── visConstants.h
│   │   └── window
│   │       └── initWindow2.h
│   ├── history
│   │   ├── command.h
│   │   ├── history.h
│   │   └── historyRecord.h
│   ├── image.h
│   ├── inspector
│   │   └── inspector.h
│   ├── loadPts.h
│   ├── main.cpp
│   ├── pipeline
│   │   ├── job.h
│   │   └── pipeline.h
│   ├── priorityQueue.h
│   ├── read
│   │   ├── delete.h
│   │   ├── imageRead
│   │   │   ├── readJPEG.h
│   │   │   ├── readPNG.h
│   │   │   └── readPPM.h
│   │   ├── imageWrite
│   │   │   ├── writeJPEG.h
│   │   │   ├── writePNG.h
│   │   │   └── writePPM.h
│   │   ├── mainLogic
│   │   │   ├── deleter.h
│   │   │   ├── reader.h
│   │   │   └── writer.h
│   │   ├── read.h
│   │   ├── readImage.h
│   │   ├── write.h
│   │   └── writeImage.h
│   └── stack.h
└── tests
    ├── test.cpp
    └── verify_operations.cpp

37 directories, 119 files (C++ Source and Header Files)

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
