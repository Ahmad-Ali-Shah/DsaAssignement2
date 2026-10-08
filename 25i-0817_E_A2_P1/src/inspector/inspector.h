#pragma once
#include <iostream>
#include "../history/history.h"
#include "../pipeline/pipeline.h"

class DataStructureInspector {
public:
    static void display(const HistoryManager& history, const ProcessingPipeline& pipeline) {
        std::cout << "\n========================================================\n";
        std::cout << "               DATA STRUCTURE INSPECTOR                 \n";
        std::cout << "========================================================\n";

        std::cout << "1. Stack Metrics:\n";
        std::cout << "   - Undo Stack Size: " << history.getUndoSize() << "\n";
        std::cout << "   - Redo Stack Size: " << history.getRedoSize() << "\n";
        std::cout << "   - Total Push Operations: " << history.getPushCount() << "\n";
        std::cout << "   - Total Pop Operations:  " << history.getPopCount() << "\n";

        std::cout << "\n2. Queue Metrics:\n";
        std::cout << "   - Current Queue Size:      " << pipeline.getCurrentQueueSize() << "\n";
        std::cout << "   - Max Recorded Queue Size: " << pipeline.getMaxRecordedQueueSize() << "\n";
        std::cout << "   - Total addQueue Calls:    " << pipeline.getAddCount() << "\n";
        std::cout << "   - Total deleteQueue Calls: " << pipeline.getDeleteCount() << "\n";

        std::cout << "\n3. Data Structure Contents:\n";
        std::cout << "   - Undo Stack (Top to Bottom): ";
        history.printUndoContents();
        std::cout << "   - Redo Stack (Top to Bottom): ";
        history.printRedoContents();
        std::cout << "   - Pending Jobs (Front to Rear): ";
        pipeline.printPendingJobNames();

        std::cout << "========================================================\n\n";
    }
};
