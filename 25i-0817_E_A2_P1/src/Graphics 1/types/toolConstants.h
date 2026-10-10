#pragma once

namespace GraphicsTool {
    const int NONE = 0;
    const int LOAD = 1;
    const int CROP = 2;
    const int ROTATE_90 = 3;
    const int ROTATE_180 = 4;
    const int ROTATE_270 = 5;
    const int FLIP_H = 6;
    const int FLIP_V = 7;
    const int BRIGHTNESS_UP = 8;
    const int BRIGHTNESS_DOWN = 9;
    const int GRAYSCALE = 10;
    const int ENQUEUE_RESIZE = 11;
    const int ENQUEUE_BLUR = 12;
    const int ENQUEUE_BUCKET_STACK = 13;
    const int ENQUEUE_BUCKET_QUEUE = 14;
    const int ENQUEUE_SAVE = 15;
    const int ENQUEUE_EXPORT = 16;
    const int PROCESS_NEXT = 17;
    const int PROCESS_ALL = 18;
    const int CLEAR_PIPELINE = 19;
    const int UNDO = 20;
    const int REDO = 21;
    const int TOGGLE_INSPECTOR = 22;
}
