#pragma once
#include <iostream>
#include <iomanip>
#include "../history/history.h"
#include "../pipeline/pipeline.h"

class DataStructureInspector {
public:
    static void display(const HistoryManager& history, const ProcessingPipeline& pipeline) {
        std::cout << "\n========================================================\n";
        std::cout << "          PHASE 2 DATA STRUCTURE & MEMORY INSPECTOR     \n";
        std::cout << "========================================================\n";

        std::cout << "1. Memory-Aware History Metrics (Section 7.1):\n";
        std::cout << "   - Memory Budget:          " << (history.getMemoryBudget() / 1024) << " KB\n";
        std::cout << "   - Current Memory Used:    " << (history.getCurrentMemoryUsage() / 1024.0) << " KB\n";
        std::cout << "   - Budget Utilization:     " << std::fixed << std::setprecision(1)
                  << ((double)history.getCurrentMemoryUsage() / history.getMemoryBudget() * 100.0) << "%\n";
        std::cout << "   - Oldest Records Evicted: " << history.getDiscardedRecordsCount() << "\n";
        std::cout << "   - Undo Stack Size:        " << history.getUndoSize() << "\n";
        std::cout << "   - Redo Stack Size:        " << history.getRedoSize() << "\n";
        std::cout << "   - Total Pushes:           " << history.getPushCount() << "\n";
        std::cout << "   - Total Pops:             " << history.getPopCount() << "\n";

        std::cout << "\n2. Scheduler & Queue Metrics (Section 7.3):\n";
        std::cout << "   - Current Mode:           " << (pipeline.getMode() == SchedulerMode::fifo ? "FIFO" : "PRIORITY (Barrier-Aware)") << "\n";
        std::cout << "   - Pending Jobs Count:     " << pipeline.getCurrentQueueSize() << "\n";

        std::cout << "\n3. History Stack Contents (Compact Records):\n";
        std::cout << "   - Undo Stack (Top to Bottom): ";
        history.printUndoContents();
        std::cout << "   - Redo Stack (Top to Bottom): ";
        history.printRedoContents();

        std::cout << "========================================================\n\n";
    }
};
