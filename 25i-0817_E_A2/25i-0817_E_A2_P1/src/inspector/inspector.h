#pragma once
#include <iostream>
#include "../history/history.h"
#include "../pipeline/pipeline.h"

using namespace std;

class DataStructureInspector {
public:
    static void display(const HistoryManager& history, const ProcessingPipeline& pipeline) {
        cout << "\n========================================================\n";
        cout << "               DATA STRUCTURE INSPECTOR                 \n";
        cout << "========================================================\n";

        cout << "1. Stack Metrics:\n";
        cout << "   - Undo Stack Size: " << history.getUndoSize() << "\n";
        cout << "   - Redo Stack Size: " << history.getRedoSize() << "\n";
        cout << "   - Total Push Operations: " << history.getPushCount() << "\n";
        cout << "   - Total Pop Operations:  " << history.getPopCount() << "\n";

        cout << "\n2. Queue Metrics:\n";
        cout << "   - Current Queue Size:      " << pipeline.getCurrentQueueSize() << "\n";
        cout << "   - Max Recorded Queue Size: " << pipeline.getMaxRecordedQueueSize() << "\n";
        cout << "   - Total addQueue Calls:    " << pipeline.getAddCount() << "\n";
        cout << "   - Total deleteQueue Calls: " << pipeline.getDeleteCount() << "\n";

        cout << "\n3. Data Structure Contents:\n";
        cout << "   - Undo Stack (Top to Bottom): ";
        history.printUndoContents();
        cout << "   - Redo Stack (Top to Bottom): ";
        history.printRedoContents();
        cout << "   - Pending Jobs (Front to Rear): ";
        pipeline.printPendingJobNames();

        cout << "========================================================\n\n";
    }
};
