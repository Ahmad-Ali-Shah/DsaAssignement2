#pragma once

namespace EditorConstants {
    const int OP_NONE = 0;
    const int OP_LOAD = 1;
    const int OP_CROP = 2;
    const int OP_ROT_90 = 3;
    const int OP_ROT_180 = 4;
    const int OP_ROT_270 = 5;
    const int OP_ROT_360 = 6;
    const int OP_FLIP_H = 7;
    const int OP_FLIP_V = 8;
    const int OP_GRAYSCALE = 9;
    const int OP_BRIGHTNESS = 10;
    const int OP_BLUR = 11;
    const int OP_RESIZE = 12;
    const int OP_BUCKET_FILL = 13;
    const int OP_RELOAD = 14;
    const int OP_SAVE = 15;

    // Sprite cut coordinates from user specification
    const int LOAD_FRAME_X = 143;
    const int LOAD_FRAME_Y = 31;
    const int LOAD_FRAME_W = 232;
    const int LOAD_FRAME_H = 138;

    const int ROT_90_X = 50;
    const int ROT_90_Y = 15;
    const int ROT_90_W = 156;
    const int ROT_90_H = 123;

    const int ROT_180_X = 266;
    const int ROT_180_Y = 12;
    const int ROT_180_W = 165;
    const int ROT_180_H = 125;

    const int ROT_270_X = 492;
    const int ROT_270_Y = 6;
    const int ROT_270_W = 161;
    const int ROT_270_H = 137;

    const int ROT_360_X = 751;
    const int ROT_360_Y = 26;
    const int ROT_360_W = 96;
    const int ROT_360_H = 105;

    const int TOOL_BLUR_X = 34;
    const int TOOL_BLUR_Y = 27;
    const int TOOL_BLUR_W = 204;
    const int TOOL_BLUR_H = 170;

    const int TOOL_BUCKET_X = 490;
    const int TOOL_BUCKET_Y = 13;
    const int TOOL_BUCKET_W = 199;
    const int TOOL_BUCKET_H = 198;

    const int TOOL_RESIZE_X = 921;
    const int TOOL_RESIZE_Y = 19;
    const int TOOL_RESIZE_W = 247;
    const int TOOL_RESIZE_H = 183;

    const int ADJ_GRAY_X = 10;
    const int ADJ_GRAY_Y = 0;
    const int ADJ_GRAY_W = 109;
    const int ADJ_GRAY_H = 109;

    const int ADJ_BRIGHT_X = 186;
    const int ADJ_BRIGHT_Y = 0;
    const int ADJ_BRIGHT_W = 78;
    const int ADJ_BRIGHT_H = 113;

    const int ADJ_CONTRAST_X = 329;
    const int ADJ_CONTRAST_Y = 0;
    const int ADJ_CONTRAST_W = 125;
    const int ADJ_CONTRAST_H = 118;
}
