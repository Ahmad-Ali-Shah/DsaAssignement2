#include <iostream>
#include <string>
#include "image.h"
#include "loadPts.h"
#include "coreImageFunctions/brightness.h"
#include "coreImageFunctions/greyScale.h"
#include "coreImageFunctions/flip.h"
#include "coreImageFunctions/rotation.h"
#include "coreImageFunctions/crop.h"
#include "coreImageFunctions/resize.h"
#include "coreImageFunctions/blur.h"
#include "coreImageFunctions/bucketFillStructBased.h"
#include "coreImageFunctions/bucketFillQueueBased.h"
#include "history/history.h"
#include "pipeline/pipeline.h"
#include "inspector/inspector.h"
#include "Graphics 1/app/runGraphics1.h"

using namespace std;

void printMenu() {
    cout << "\n========================================================\n";
    cout << "             IMAGELAB: CORE IMAGE EDITOR                \n";
    cout << "========================================================\n";
    cout << " [1]  Load Image (Instant)\n";
    cout << " [2]  Crop (Instant)\n";
    cout << " [3]  Rotate (Instant)\n";
    cout << " [4]  Flip (Instant)\n";
    cout << " [5]  Brightness (Instant)\n";
    cout << " [6]  Grayscale (Instant)\n";
    cout << "--------------------------------------------------------\n";
    cout << " [7]  Queue Resize (Queued)\n";
    cout << " [8]  Queue Blur (Queued)\n";
    cout << " [9]  Queue Bucket Fill (Queued: Stack or Queue)\n";
    cout << " [10] Queue Save Project (Queued)\n";
    cout << " [11] Queue Export (Queued)\n";
    cout << "--------------------------------------------------------\n";
    cout << " [12] List Pending Jobs\n";
    cout << " [13] Process Next Job\n";
    cout << " [14] Process All Jobs\n";
    cout << " [15] Cancel Pending Job\n";
    cout << "--------------------------------------------------------\n";
    cout << " [16] Undo Last Action\n";
    cout << " [17] Redo Action\n";
    cout << " [18] View Data Structure Inspector\n";
    cout << " [19] Launch Interactive Studio GUI (SFML)\n";
    cout << " [0]  Exit\n";
    cout << "========================================================\n";
    cout << "Enter your choice: ";
}

int main() {
    Pixel** activeImage = nullptr;
    int width = 0;
    int height = 0;
    string activeFile = "";

    HistoryManager history(50);
    ProcessingPipeline pipeline(30);

    cout << "========================================================\n";
    cout << "                    WELCOME TO IMAGELAB                 \n";
    cout << "========================================================\n";
    cout << " Please choose how you want to run ImageLab:\n";
    cout << " [1] Text Menu (Run right here in this black box terminal)\n";
    cout << " [2] Graphical Window (Open interactive graphics window)\n";
    cout << "========================================================\n";
    cout << "Enter 1 or 2: ";
    int startMode = 1;
    if (cin >> startMode && startMode == 2) {
        cout << "[ImageLab] Launching Graphical Window...\n";
        GraphicsApp::runGraphics1(activeImage, width, height, history, pipeline);
        if (activeImage) ReadPath::freeImage(activeImage, height);
        return 0;
    }

    cout << "\nWelcome to ImageLab (Phase 1 Image Studio)\n";

    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!(cin >> choice)) {
            if (cin.eof()) {
                break;
            }
            cin.clear();
            string ignore;
            cin >> ignore;
            continue;
        }

        if (choice == 0) {
            cout << "Exiting ImageLab. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: { // Load Image
                string path;
                int w = 0, h = 0;
                cout << "Enter image file path: ";
                cin >> path;
                cout << "Enter width (or 0 for PPM automatic detection): ";
                cin >> w;
                cout << "Enter height (or 0 for PPM automatic detection): ";
                cin >> h;

                if (activeImage) {
                    ReadPath::freeImage(activeImage, height);
                }
                activeImage = ReadPath::Read(path, w, h);
                if (activeImage) {
                    width = (w > 0) ? w : 100;
                    height = (h > 0) ? h : 100;
                    activeFile = path;
                    cout << "[Success] Image loaded (" << width << "x" << height << ") from: " << path << "\n";
                }
                break;
            }

            case 2: { // Crop
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                int x1, y1, w, h;
                cout << "Enter starting X: "; cin >> x1;
                cout << "Enter starting Y: "; cin >> y1;
                cout << "Enter crop width: "; cin >> w;
                cout << "Enter crop height: "; cin >> h;

                history.recordAction("Crop", activeImage, width, height);
                activeImage = myCrop::applyCrop(activeImage, width, height, x1, y1, w, h);
                cout << "[Success] Image cropped to " << width << "x" << height << "\n";
                break;
            }

            case 3: { // Rotate
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                int angle;
                cout << "Enter angle (90, 180, 270): ";
                cin >> angle;
                history.recordAction("Rotate " + to_string(angle), activeImage, width, height);
                activeImage = rotateObject::applyRotate(activeImage, width, height, angle);
                cout << "[Success] Rotated by " << angle << " degrees. Dimensions: " << width << "x" << height << "\n";
                break;
            }

            case 4: { // Flip
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                int dir;
                cout << "Direction (1 = Horizontal, 2 = Vertical): ";
                cin >> dir;
                if (dir == 1) {
                    history.recordAction("Flip Horizontal", activeImage, width, height);
                    flipAxis::applyFlipHorizontal(activeImage, width, height);
                    cout << "[Success] Flipped horizontally.\n";
                } else {
                    history.recordAction("Flip Vertical", activeImage, width, height);
                    flipAxis::applyFlipVertical(activeImage, width, height);
                    cout << "[Success] Flipped vertically.\n";
                }
                break;
            }

            case 5: { // Brightness
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                double delta;
                cout << "Enter brightness adjustment delta (-255 to +255): ";
                cin >> delta;
                history.recordAction("Brightness", activeImage, width, height);
                MyBrightness::applyBrightness(activeImage, width, height, delta);
                cout << "[Success] Brightness adjusted by " << delta << "\n";
                break;
            }

            case 6: { // Grayscale
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                history.recordAction("Grayscale", activeImage, width, height);
                MygreyScale::applyGrayscale(activeImage, width, height);
                cout << "[Success] Converted to Grayscale.\n";
                break;
            }

            case 7: { // Queue Resize
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                int tw, th;
                cout << "Enter target width: "; cin >> tw;
                cout << "Enter target height: "; cin >> th;
                Job j(0, JobType::resize, "Resize to " + to_string(tw) + "x" + to_string(th));
                j.targetW = tw;
                j.targetH = th;
                pipeline.addJob(j);
                break;
            }

            case 8: { // Queue Blur
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                Job j(0, JobType::blur, "Blur (3x3 Kernel)");
                pipeline.addJob(j);
                break;
            }

            case 9: { // Queue Bucket Fill
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                int sx, sy, vr, vg, vb, typeChoice;
                cout << "Enter starting pixel X: "; cin >> sx;
                cout << "Enter starting pixel Y: "; cin >> sy;
                cout << "Enter replacement Color R: "; cin >> vr;
                cout << "Enter replacement Color G: "; cin >> vg;
                cout << "Enter replacement Color B: "; cin >> vb;
                cout << "Select traversal algorithm (1 = Stack-based DFS, 2 = Queue-based BFS): ";
                cin >> typeChoice;

                Job j(0, (typeChoice == 1) ? JobType::bucketFillStack : JobType::bucketFillQueue,
                      (typeChoice == 1) ? "BucketFill (Stack)" : "BucketFill (Queue)");
                j.startX = sx;
                j.startY = sy;
                j.r = vr; j.g = vg; j.b = vb;
                pipeline.addJob(j);
                break;
            }

            case 10: { // Queue Save Project
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                Job j(0, JobType::saveProject, "Save Project");
                j.filePath = activeFile.empty() ? "projectSaved.ppm" : activeFile;
                pipeline.addJob(j);
                break;
            }

            case 11: { // Queue Export
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                string outPath;
                cout << "Enter export file path (e.g. output.ppm): ";
                cin >> outPath;
                Job j(0, JobType::exportImage, "Export to " + outPath);
                j.filePath = outPath;
                pipeline.addJob(j);
                break;
            }

            case 12: { // List Pending Jobs
                pipeline.listPendingJobs();
                break;
            }

            case 13: { // Process Next Job
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                pipeline.processNextJob(activeImage, width, height, history);
                break;
            }

            case 14: { // Process All Jobs
                if (!activeImage) { cout << "[Error] No active image loaded.\n"; break; }
                pipeline.processAllJobs(activeImage, width, height, history);
                break;
            }

            case 15: { // Cancel Pending Job
                int id;
                cout << "Enter Job ID to cancel: ";
                cin >> id;
                pipeline.cancelJob(id);
                break;
            }

            case 16: { // Undo
                if (!pipeline.isEmpty()) {
                    cout << "[Info] Jobs are pending in the pipeline! Complete them before undoing.\n";
                } else if (history.undo(activeImage, width, height)) {
                    cout << "[Success] Undone! Current dimensions: " << width << "x" << height << "\n";
                } else {
                    cout << "[Undo Stack Empty] Nothing to undo.\n";
                }
                break;
            }

            case 17: { // Redo
                if (!pipeline.isEmpty()) {
                    cout << "[Info] Jobs are pending in the pipeline! Complete them before redoing.\n";
                } else if (history.redo(activeImage, width, height)) {
                    cout << "[Success] Redone! Current dimensions: " << width << "x" << height << "\n";
                } else {
                    cout << "[Redo Stack Empty] Nothing to redo.\n";
                }
                break;
            }

            case 18: { // Inspector
                DataStructureInspector::display(history, pipeline);
                break;
            }

            case 19: { // Interactive GUI
                cout << "[ImageLab] Launching Graphical Studio GUI...\n";
                GraphicsApp::runGraphics1(activeImage, width, height, history, pipeline);
                cout << "[ImageLab] Returned to Console Menu.\n";
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    if (activeImage) {
        ReadPath::freeImage(activeImage, height);
    }
    return 0;
}
