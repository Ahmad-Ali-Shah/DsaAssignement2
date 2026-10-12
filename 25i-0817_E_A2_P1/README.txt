========================================================================
             ImageLab - Phase 1 (Data Structures & Core Editor)
             Roll Number: 25i-0817 | Section: E | Assignment 2
========================================================================

Directory Structure (C++ Headers & Source Files):
-------------------------------------------------
25i-0817_E_A2_P1
├── src
│   ├── CircularQueue.h
│   ├── coreImageFunctions
│   │   ├── APPLYopperations
│   │   │   ├── applyBlur.h
│   │   │   ├── applyBrightness.h
│   │   │   ├── applyCrop.h
│   │   │   ├── applyFlip.h
│   │   │   ├── applyGreyScale.h
│   │   │   ├── applyResize.h
│   │   │   └── applyRotation.h
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
│   ├── Graphics 1
│   │   ├── animator
│   │   │   ├── loadSpriteSheet.h
│   │   │   ├── renderDataStructureAnimation.h
│   │   │   └── renderSpriteCard.h
│   │   ├── app
│   │   │   ├── handleToolExecution.h
│   │   │   ├── renderApp.h
│   │   │   ├── resolveAssetPath.h
│   │   │   └── runGraphics1.h
│   │   ├── canvas
│   │   │   ├── createTextureFromPixels.h
│   │   │   ├── getCanvasPixelCoords.h
│   │   │   └── renderCanvas.h
│   │   ├── cursor
│   │   │   └── cursor.h
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
│   │   ├── inspectorView
│   │   │   └── renderInspectorHUD.h
│   │   ├── pipelineView
│   │   │   ├── renderJobCard.h
│   │   │   └── renderPipelineBar.h
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
│   │   │   ├── drawBox.h
│   │   │   ├── drawText.h
│   │   │   └── loadFont.h
│   │   ├── toolbar
│   │   │   ├── detectToolClick.h
│   │   │   ├── renderToolButton.h
│   │   │   └── renderToolPanel.h
│   │   ├── types
│   │   │   └── toolConstants.h
│   │   ├── visPage
│   │   │   ├── loadVisAssets.h
│   │   │   ├── renderDataWindow.h
│   │   │   ├── renderVisControls.h
│   │   │   ├── runVisPage.h
│   │   │   ├── updateVisAnimation.h
│   │   │   └── visConstants.h
│   │   └── window
│   │       └── initWindow.h
│   ├── history
│   │   ├── command.h
│   │   └── history.h
│   ├── image.h
│   ├── inspector
│   │   └── inspector.h
│   ├── loadPts.h
│   ├── main.cpp
│   ├── pipeline
│   │   ├── job.h
│   │   └── pipeline.h
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
    ├── queueTest.cpp
    ├── stackTest.cpp
    └── test.cpp

36 directories, 122 files (C++ Source and Header Files)

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
   ./src/main          # Interactive mode prompt: [1] Console Menu  [2] SFML GUI Studio
   ./src/main --gui    # Launch Graphical User Interface directly
   ./src/main --cli    # Launch Terminal / Console Menu Mode directly

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
