#include <iostream>
#include <string>
#include "image.h"
#include "read/read.h"
#include "read/write.h"
#include "read/delete.h"
#include "history/history.h"
#include "pipeline/pipeline.h"
#include "inspector/inspector.h"
#include "benchmarks.h"
#include "Graphics 2/app/runGraphics2.h"

// Modular Core Operations
#include "coreImageFunctions/brightness/brightness.h"
#include "coreImageFunctions/brightness/applyBrightness.h"
#include "coreImageFunctions/greyScale/greyScale.h"
#include "coreImageFunctions/greyScale/applyGreyScale.h"
#include "coreImageFunctions/flip/flip.h"
#include "coreImageFunctions/flip/applyFlip.h"
#include "coreImageFunctions/rotation/rotation.h"
#include "coreImageFunctions/rotation/applyRotation.h"
#include "coreImageFunctions/Crop/crop.h"
#include "coreImageFunctions/Crop/applyCrop.h"
#include "coreImageFunctions/resize/resize.h"
#include "coreImageFunctions/resize/applyResize.h"
#include "coreImageFunctions/blur/blur.h"
#include "coreImageFunctions/blur/applyBlur.h"
#include "coreImageFunctions/bucketFill/bucketFillStructBased.h"
#include "coreImageFunctions/bucketFill/bucketFillQueueBased.h"

using namespace std;

void printMenu() {
    cout << "\n=======================================================\n";
    cout << "        IMAGELAB - PHASE 2: ADVANCED SYSTEM ENGINE     \n";
    cout << "=======================================================\n";
    cout << " [1]  Load Image (PPM / Binary)\n";
    cout << " [2]  Save Image\n";
    cout << " [3]  Adjust Brightness (Auto-Coalesced, Clipped Aware)\n";
    cout << " [4]  Convert to Grayscale\n";
    cout << " [5]  Flip Image (Horizontal / Vertical)\n";
    cout << " [6]  Rotate Image (90 / 180 / 270 deg)\n";
    cout << " [7]  Crop Image\n";
    cout << " [8]  Resize Image\n";
    cout << " [9]  Apply Blur Filter\n";
    cout << " [10] Bucket Fill (Stack-based DFS)\n";
    cout << " [11] Bucket Fill (Queue-based BFS)\n";
    cout << " [12] Undo Last Action (Compact Delta)\n";
    cout << " [13] Redo Action\n";
    cout << " [14] Pipeline: Add Job to Scheduler\n";
    cout << " [15] Pipeline: List Pending Jobs\n";
    cout << " [16] Pipeline: Process Next Job\n";
    cout << " [17] Pipeline: Process All Jobs\n";
    cout << " [18] Pipeline: Switch Mode (FIFO vs Priority)\n";
    cout << " [19] Benchmark: 30-Job Workload Comparison (Section 7.3)\n";
    cout << " [20] Benchmark: Single vs Batched Operations (Section 7.4)\n";
    cout << " [21] Memory: Set Budget & Configure Eviction (Section 7.1)\n";
    cout << " [22] Inspector: Data Structure & Memory Status\n";
    cout << " [23] Launch Interactive Studio GUI (SFML)\n";
    cout << " [0]  Exit\n";
    cout << "-------------------------------------------------------\n";
    cout << "Enter choice: ";
}

int main() {
    Pixel** currentImage = nullptr;
    int width = 0;
    int height = 0;

    // Configurable 5 MB budget default
    HistoryManager history(5 * 1024 * 1024);
    ProcessingPipeline pipeline(100, SchedulerMode::priority);

    cout << "========================================================\n";
    cout << "                 WELCOME TO IMAGELAB P2                 \n";
    cout << "========================================================\n";
    cout << " Please choose how you want to run ImageLab:\n";
    cout << " [1] Text Menu (Run right here in this black box terminal)\n";
    cout << " [2] Graphical Window (Open interactive graphics window)\n";
    cout << "========================================================\n";
    cout << "Enter 1 or 2: ";
    int startMode = 1;
    if (cin >> startMode && startMode == 2) {
        cout << "[ImageLab P2] Launching Graphical Window...\n";
        GraphicsApp2::runGraphics2(currentImage, width, height, history, pipeline);
        if (currentImage) ReadPath::freeImage(currentImage, height);
        return 0;
    }

    int choice = -1;

    while (choice != 0) {
        printMenu();
        if (!(cin >> choice)) {
            if (cin.eof()) {
                break;
            }
            cin.clear();
            string discard;
            cin >> discard;
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "Enter file path to load: ";
                string path;
                cin >> path;
                if (currentImage) {
                    ReadPath::freeImage(currentImage, height);
                    currentImage = nullptr;
                }
                currentImage = ReadPath::Read(path, width, height);
                if (currentImage) {
                    cout << "[Success] Loaded image: " << width << "x" << height << "\n";
                } else {
                    cout << "[Error] Failed to load image from " << path << "\n";
                }
                break;
            }
            case 2: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                cout << "Enter file path to save: ";
                string path;
                cin >> path;
                ReadPath::Write(path, currentImage, width, height, true);
                cout << "[Success] Image saved to " << path << "\n";
                break;
            }
            case 3: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                cout << "Enter brightness delta (-255 to 255): ";
                double delta;
                cin >> delta;
                history.recordBrightness(delta, currentImage, width, height);
                MyBrightness::applyBrightness(currentImage, width, height, delta);
                cout << "[Success] Brightness applied!\n";
                break;
            }
            case 4: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                history.recordGridOperation("Grayscale", HistoryOpType::grayscale, currentImage, width, height);
                MygreyScale::applyGrayscale(currentImage, width, height);
                cout << "[Success] Grayscale applied!\n";
                break;
            }
            case 5: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                cout << "Flip: 1 for Horizontal, 2 for Vertical: ";
                int flipOpt;
                cin >> flipOpt;
                bool isH = (flipOpt == 1);
                history.recordFlip(isH, width, height);
                if (isH) flipAxis::applyFlipHorizontal(currentImage, width, height);
                else flipAxis::applyFlipVertical(currentImage, width, height);
                cout << "[Success] Flip applied!\n";
                break;
            }
            case 6: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                cout << "Enter rotation angle (90, 180, 270): ";
                int angle;
                cin >> angle;
                history.recordRotate(angle, width, height);
                currentImage = rotateObject::applyRotate(currentImage, width, height, angle);
                cout << "[Success] Image rotated! New dimensions: " << width << "x" << height << "\n";
                break;
            }
            case 7: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                int sx, sy, cw, ch;
                cout << "Enter startX startY cropWidth cropHeight: ";
                cin >> sx >> sy >> cw >> ch;
                history.recordGridOperation("Crop", HistoryOpType::crop, currentImage, width, height);
                currentImage = myCrop::applyCrop(currentImage, width, height, sx, sy, cw, ch);
                cout << "[Success] Image cropped! New dimensions: " << width << "x" << height << "\n";
                break;
            }
            case 8: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                int tw, th;
                cout << "Enter targetWidth targetHeight: ";
                cin >> tw >> th;
                history.recordGridOperation("Resize", HistoryOpType::resize, currentImage, width, height);
                currentImage = scaling::applyResize(currentImage, width, height, tw, th);
                cout << "[Success] Image resized to: " << width << "x" << height << "\n";
                break;
            }
            case 9: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                history.recordGridOperation("Blur", HistoryOpType::blur, currentImage, width, height);
                FrobeniusMatrixInnerProductForBlurr::applyBlur(currentImage, width, height);
                cout << "[Success] Blur applied!\n";
                break;
            }
            case 10: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                int sx, sy;
                unsigned int r, g, b;
                cout << "Enter startX startY newR newG newB: ";
                cin >> sx >> sy >> r >> g >> b;
                if (sx >= 0 && sx < width && sy >= 0 && sy < height) {
                    Pixel orig = currentImage[sy][sx];
                    Pixel target{r, g, b};
                    Point* changed = new Point[width * height];
                    int changedCount = 0;
                    MybucketFill::ReplaceNearOne(currentImage, width, height, sx, sy, r, g, b);
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            if (currentImage[y][x] == target) {
                                changed[changedCount++] = {x, y};
                            }
                        }
                    }
                    history.recordBucketFill(orig, target, changed, changedCount, width, height);
                    delete[] changed;
                    cout << "[Success] Stack-based Bucket Fill applied! (" << changedCount << " pixels filled)\n";
                }
                break;
            }
            case 11: {
                if (!currentImage) { cout << "No image loaded!\n"; break; }
                int sx, sy;
                unsigned int r, g, b;
                cout << "Enter startX startY newR newG newB: ";
                cin >> sx >> sy >> r >> g >> b;
                if (sx >= 0 && sx < width && sy >= 0 && sy < height) {
                    Pixel orig = currentImage[sy][sx];
                    Pixel target{r, g, b};
                    Point* changed = new Point[width * height];
                    int changedCount = 0;
                    MybucketFill::ReplaceNearOneQueue(currentImage, width, height, sx, sy, r, g, b);
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            if (currentImage[y][x] == target) {
                                changed[changedCount++] = {x, y};
                            }
                        }
                    }
                    history.recordBucketFill(orig, target, changed, changedCount, width, height);
                    delete[] changed;
                    cout << "[Success] Queue-based Bucket Fill applied! (" << changedCount << " pixels filled)\n";
                }
                break;
            }
            case 12: {
                if (history.undo(currentImage, width, height)) {
                    cout << "[Success] Undone! Current image: " << width << "x" << height << "\n";
                } else {
                    cout << "[Undo] Nothing to undo.\n";
                }
                break;
            }
            case 13: {
                if (history.redo(currentImage, width, height)) {
                    cout << "[Success] Redone! Current image: " << width << "x" << height << "\n";
                } else {
                    cout << "[Redo] Nothing to redo.\n";
                }
                break;
            }
            case 14: {
                cout << "Job Type: [1] Undo/Redo(Pri:1), [2] Blur(Pri:2), [3] Resize(Pri:3), [4] Export Barrier(Pri:4): ";
                int jt; cin >> jt;
                if (jt == 1) {
                    pipeline.addJob(Job(0, JobType::undoRedo, "Undo Job", 1));
                } else if (jt == 2) {
                    pipeline.addJob(Job(0, JobType::blur, "Blur Job", 2));
                } else if (jt == 3) {
                    int tw, th;
                    cout << "Enter targetWidth targetHeight: ";
                    cin >> tw >> th;
                    Job j(0, JobType::resize, "Resize Job", 3);
                    j.targetW = tw; j.targetH = th;
                    pipeline.addJob(j);
                } else if (jt == 4) {
                    cout << "Enter export file path: ";
                    string fp; cin >> fp;
                    Job j(0, JobType::exportImage, "Export Barrier", 4);
                    j.filePath = fp;
                    pipeline.addJob(j);
                }
                break;
            }
            case 15:
                pipeline.listPendingJobs();
                break;
            case 16:
                if (!currentImage) { cout << "No image loaded to run pipeline job on!\n"; break; }
                pipeline.processNextJob(currentImage, width, height, history);
                break;
            case 17:
                if (!currentImage) { cout << "No image loaded to run pipeline jobs on!\n"; break; }
                pipeline.processAllJobs(currentImage, width, height, history);
                break;
            case 18: {
                cout << "Select Mode: [1] FIFO, [2] PRIORITY: ";
                int m; cin >> m;
                pipeline.setMode(m == 1 ? SchedulerMode::fifo : SchedulerMode::priority);
                break;
            }
            case 19:
                pipeline.runBenchmarkComparison();
                break;
            case 20:
                BenchmarkRunner::runBatchBenchmarks();
                break;
            case 21: {
                cout << "Enter new memory budget in KB (e.g., 5120 for 5MB, 50 for 50KB to test eviction): ";
                int kb; cin >> kb;
                history.setMemoryBudget(kb * 1024);
                cout << "[Success] Memory budget updated to " << kb << " KB\n";
                break;
            }
            case 22:
                DataStructureInspector::display(history, pipeline);
                break;
            case 23: {
                cout << "[ImageLab P2] Launching Graphical Studio GUI...\n";
                GraphicsApp2::runGraphics2(currentImage, width, height, history, pipeline);
                cout << "[ImageLab P2] Returned to Console Menu.\n";
                break;
            }
            case 0:
                cout << "Exiting ImageLab Phase 2. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    if (currentImage) {
        ReadPath::freeImage(currentImage, height);
        currentImage = nullptr;
    }
    return 0;
}
