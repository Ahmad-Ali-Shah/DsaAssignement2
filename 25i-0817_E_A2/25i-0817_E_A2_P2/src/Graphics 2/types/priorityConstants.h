#pragma once

namespace GraphicsTool2 {
    const int none = 0;
    const int load = 1;
    const int crop = 2;
    const int rotate90 = 3;
    const int flipH = 4;
    const int brightnessUp = 5;
    const int grayscale = 6;
    const int undo = 7;
    const int redo = 8;
    const int enqueueResize = 9;
    const int enqueueBlur = 10;
    const int enqueueBucketStack = 11;
    const int enqueueBucketQueue = 12;
    const int enqueueSave = 13;
    const int enqueueExport = 14;
    const int processNext = 15;
    const int processAll = 16;
    const int toggleMode = 17;
    const int runBenchmark = 18;
    const int toggleDualFill = 19;
    const int clearPipeline = 20;
}
