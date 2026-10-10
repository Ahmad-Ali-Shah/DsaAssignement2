#pragma once

namespace GraphicsTool2 {
    const int NONE = 0;
    const int LOAD = 1;
    const int CROP = 2;
    const int ROTATE_90 = 3;
    const int FLIP_H = 4;
    const int BRIGHTNESS_UP = 5;
    const int GRAYSCALE = 6;
    const int UNDO = 7;
    const int REDO = 8;
    const int ENQUEUE_RESIZE = 9;
    const int ENQUEUE_BLUR = 10;
    const int ENQUEUE_BUCKET_STACK = 11;
    const int ENQUEUE_BUCKET_QUEUE = 12;
    const int ENQUEUE_SAVE = 13;
    const int ENQUEUE_EXPORT = 14;
    const int PROCESS_NEXT = 15;
    const int PROCESS_ALL = 16;
    const int TOGGLE_MODE = 17;
    const int RUN_BENCHMARK = 18;
    const int TOGGLE_DUAL_FILL = 19;
    const int CLEAR_PIPELINE = 20;
}
