#pragma once
#include <iostream>
#include <iomanip>
#include "../history/history.h"
#include "../pipeline/pipeline.h"

using namespace std;

class DataStructureInspector {
public:
    static void display(const HistoryManager& history, const ProcessingPipeline& pipeline) {
        cout << "\n========================================================\n";
        cout << "          PHASE 2 DATA STRUCTURE & MEMORY INSPECTOR     \n";
        cout << "========================================================\n";

        cout << "1. Memory-Aware History Metrics (Section 7.1):\n";
        cout << "   - Memory Budget:          " << (history.getMemoryBudget() / 1024) << " KB\n";
        cout << "   - Current Memory Used:    " << (history.getCurrentMemoryUsage() / 1024.0) << " KB\n";
        cout << "   - Budget Utilization:     " << fixed << setprecision(1)
                  << ((double)history.getCurrentMemoryUsage() / history.getMemoryBudget() * 100.0) << "%\n";
        cout << "   - Oldest Records Evicted: " << history.getDiscardedRecordsCount() << "\n";
        cout << "   - Undo Stack Size:        " << history.getUndoSize() << "\n";
        cout << "   - Redo Stack Size:        " << history.getRedoSize() << "\n";
        cout << "   - Total Pushes:           " << history.getPushCount() << "\n";
        cout << "   - Total Pops:             " << history.getPopCount() << "\n";

        cout << "\n2. Scheduler & Queue Metrics (Section 7.3):\n";
        cout << "   - Current Mode:           " << (pipeline.getMode() == SchedulerMode::fifo ? "FIFO" : "PRIORITY (Barrier-Aware)") << "\n";
        cout << "   - Pending Jobs Count:     " << pipeline.getCurrentQueueSize() << "\n";

        cout << "\n3. History Stack Contents (Compact Records):\n";
        cout << "   - Undo Stack (Top to Bottom): ";
        history.printUndoContents();
        cout << "   - Redo Stack (Top to Bottom): ";
        history.printRedoContents();

        cout << "========================================================\n\n";
    }
};
