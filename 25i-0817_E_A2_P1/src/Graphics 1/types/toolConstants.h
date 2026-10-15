#pragma once

namespace GraphicsTool {
    const int none = 0;
    const int load = 1;
    const int crop = 2;
    const int rotate90 = 3;
    const int rotate180 = 4;
    const int rotate270 = 5;
    const int flipH = 6;
    const int flipV = 7;
    const int brightnessUp = 8;
    const int brightnessDown = 9;
    const int grayscale = 10;
    const int enqueueResize = 11;
    const int enqueueBlur = 12;
    const int enqueueBucketStack = 13;
    const int enqueueBucketQueue = 14;
    const int enqueueSave = 15;
    const int enqueueExport = 16;
    const int processNext = 17;
    const int processAll = 18;
    const int clearPipeline = 19;
    const int undo = 20;
    const int redo = 21;
    const int toggleInspector = 22;
}
