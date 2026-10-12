========================================================================
             ImageLab - Phase 1 (Data Structures & Core Editor)
             Roll Number: 25i-0817 | Section: E | Assignment 2
========================================================================

Directory Structure:
-------------------
25i-0817_E_A2_P1
├── All Req Assests
│   ├── Adjustment.png
│   ├── arrow.png
│   ├── asteroids
│   │   ├── asteroid-1.png
│   │   ├── asteroid-2.png
│   │   ├── asteroid-3.png
│   │   ├── asteroid-4.png
│   │   └── asteroid-5.png
│   ├── background2.jpeg
│   ├── background.png
│   ├── banner.png
│   ├── Bg3.jpg
│   ├── Blocks.png
│   ├── crop.png
│   ├── fonts
│   │   ├── Awesome.ttf
│   │   ├── Cintarini.ttf
│   │   ├── CType.ttf
│   │   ├── KarmaticArcade.ttf
│   │   ├── MetalSlug.ttf
│   │   ├── Pixeboy.ttf
│   │   └── RasterForge.ttf
│   ├── imageLoad.png
│   ├── Rotations.png
│   ├── ship.png
│   ├── tools.png
│   └── white_0.png
├── assets
│   ├── cube_spritesheet_transparent.png
│   ├── fonts
│   │   ├── Awesome.ttf
│   │   ├── Cintarini.ttf
│   │   ├── CType.ttf
│   │   ├── KarmaticArcade.ttf
│   │   ├── MetalSlug.ttf
│   │   ├── Pixeboy.ttf
│   │   └── RasterForge.ttf
│   ├── imagelab_tools_spritesheet.jpg
│   ├── imagelab_tools_spritesheet.png
│   ├── stack_isolated_push_pop.jpg
│   ├── stack_isolated_push_pop.png
│   ├── stack_push_pop_error_sheet.jpg
│   ├── stack_push_pop_error_sheet.png
│   ├── stack_queue_spritesheet.jpg
│   └── stack_queue_spritesheet.png
├── background2.jpeg
├── DSA_A2.pdf
├── images
│   ├── out_blur.png
│   ├── out_blur.ppm
│   ├── out_brightness.png
│   ├── out_brightness.ppm
│   ├── out_bucket_queue.png
│   ├── out_bucket_queue.ppm
│   ├── out_bucket_stack.png
│   ├── out_bucket_stack.ppm
│   ├── out_crop.png
│   ├── out_crop.ppm
│   ├── out_flip_h.png
│   ├── out_flip_h.ppm
│   ├── out_grayscale.png
│   ├── out_grayscale.ppm
│   ├── out_resize.png
│   ├── out_resize.ppm
│   ├── out_rotate90.png
│   ├── out_rotate90.ppm
│   ├── sample.jpg
│   ├── sample.png
│   └── sample.ppm
├── images (1).jpeg
├── images_1_transparent.png
├── images (2).jpeg
├── images_2_transparent.png
├── images (3).jpeg
├── images_3_transparent.png
├── images.jpeg
├── images_transparent.png
├── p.jpeg
├── README.txt
├── report
│   ├── fast_logo.png
│   ├── report_phase1.pdf
│   └── report_phase1.tex
├── src
│   ├── CircularQueue.h
│   ├── coreImageFunctions
│   │   ├── APPLYopperations
│   │   │   ├── applyBlur.h
│   │   │   ├── applyBrightness.h
│   │   │   ├── applyCrop.h
│   │   │   ├── applyFlip.h
│   │   │   ├── applyGreyScale.h
│   │   │   ├── applyResize.h
│   │   │   └── applyRotation.h
│   │   ├── blur
│   │   │   ├── applyBlur.h
│   │   │   └── blur.h
│   │   ├── blur.h
│   │   ├── brightness
│   │   │   ├── applyBrightness.h
│   │   │   └── brightness.h
│   │   ├── brightness.h
│   │   ├── bucketFill
│   │   │   ├── bucketFill_QueueBased.h
│   │   │   └── bucketFill_StructBased.h
│   │   ├── bucketFill_QueueBased.h
│   │   ├── bucketFill_StructBased.h
│   │   ├── Crop
│   │   │   ├── applyCrop.h
│   │   │   └── Crop.h
│   │   ├── Crop.h
│   │   ├── flip
│   │   │   ├── applyFlip.h
│   │   │   └── flip.h
│   │   ├── flip.h
│   │   ├── greyScale
│   │   │   ├── applyGreyScale.h
│   │   │   └── greyScale.h
│   │   ├── greyScale.h
│   │   ├── resize
│   │   │   ├── applyResize.h
│   │   │   └── resize.h
│   │   ├── resize.h
│   │   ├── rotation
│   │   │   ├── applyRotation.h
│   │   │   └── rotation.h
│   │   └── rotation.h
│   ├── Graphics 1
│   │   ├── animator
│   │   │   ├── loadSpriteSheet.h
│   │   │   ├── renderDataStructureAnimation.h
│   │   │   └── renderSpriteCard.h
│   │   ├── app
│   │   │   ├── handleToolExecution.h
│   │   │   ├── renderApp.h
│   │   │   ├── resolveAssetPath.h
│   │   │   └── runGraphics1.h
│   │   ├── canvas
│   │   │   ├── createTextureFromPixels.h
│   │   │   ├── getCanvasPixelCoords.h
│   │   │   └── renderCanvas.h
│   │   ├── cursor
│   │   │   └── cursor.h
│   │   ├── editorPage
│   │   │   ├── editorConstants.h
│   │   │   ├── executeEditorAction.h
│   │   │   ├── loadEditorAssets.h
│   │   │   ├── renderEditorBanner.h
│   │   │   ├── renderLeftToolbar.h
│   │   │   ├── renderMiddleCanvas.h
│   │   │   ├── renderParameterModal.h
│   │   │   ├── renderRightPanel.h
│   │   │   └── runEditorPage.h
│   │   ├── homePage
│   │   │   ├── homeConstants.h
│   │   │   ├── loadAsteroidTextures.h
│   │   │   ├── loadCatTexture.h
│   │   │   ├── loadHomeFonts.h
│   │   │   ├── renderAsteroidCorner.h
│   │   │   ├── renderCatSprite.h
│   │   │   ├── renderHomePage.h
│   │   │   ├── renderHomeTitle.h
│   │   │   ├── runHomePage.h
│   │   │   └── updateCatState.h
│   │   ├── inputPage
│   │   │   ├── inputConstants.h
│   │   │   ├── loadInputAssets.h
│   │   │   ├── renderInputBackground.h
│   │   │   ├── renderInputPrompt.h
│   │   │   ├── renderLoadingScreen.h
│   │   │   ├── runInputPage.h
│   │   │   └── validateAndLoadImage.h
│   │   ├── inspectorView
│   │   │   └── renderInspectorHUD.h
│   │   ├── pipelineView
│   │   │   ├── renderJobCard.h
│   │   │   └── renderPipelineBar.h
│   │   ├── selectionPage
│   │   │   ├── loadSelectionAssets.h
│   │   │   ├── renderSelectionBackground.h
│   │   │   ├── renderSelectionOptions.h
│   │   │   ├── renderSelectionPage.h
│   │   │   ├── renderSelectionTitle.h
│   │   │   ├── renderShipCursor.h
│   │   │   ├── runSelectionPage.h
│   │   │   ├── selectionConstants.h
│   │   │   └── updateShipSpeed.h
│   │   ├── theme
│   │   │   ├── drawBox.h
│   │   │   ├── drawText.h
│   │   │   └── loadFont.h
│   │   ├── toolbar
│   │   │   ├── detectToolClick.h
│   │   │   ├── renderToolButton.h
│   │   │   └── renderToolPanel.h
│   │   ├── types
│   │   │   └── toolConstants.h
│   │   ├── visPage
│   │   │   ├── loadVisAssets.h
│   │   │   ├── renderDataWindow.h
│   │   │   ├── renderVisControls.h
│   │   │   ├── runVisPage.h
│   │   │   ├── updateVisAnimation.h
│   │   │   └── visConstants.h
│   │   └── window
│   │       └── initWindow.h
│   ├── history
│   │   ├── command.h
│   │   └── history.h
│   ├── image.h
│   ├── inspector
│   │   └── inspector.h
│   ├── loadPts.h
│   ├── main
│   ├── main.cpp
│   ├── pipeline
│   │   ├── job.h
│   │   └── pipeline.h
│   ├── read
│   │   ├── delete.h
│   │   ├── imageRead
│   │   │   ├── readJPEG.h
│   │   │   ├── readPNG.h
│   │   │   └── readPPM.h
│   │   ├── imageWrite
│   │   │   ├── writeJPEG.h
│   │   │   ├── writePNG.h
│   │   │   └── writePPM.h
│   │   ├── mainLogic
│   │   │   ├── deleter.h
│   │   │   ├── reader.h
│   │   │   └── writer.h
│   │   ├── read.h
│   │   ├── readImage.h
│   │   ├── write.h
│   │   └── writeImage.h
│   └── stack.h
├── tests
│   ├── queueTest.cpp
│   ├── stackTest.cpp
│   ├── test
│   └── test.cpp
└── TRANS-JOUR.pdf

43 directories, 202 files

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
