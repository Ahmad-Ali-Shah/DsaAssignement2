#pragma once

namespace EditorConstants {
    const int opNone = 0;
    const int opLoad = 1;
    const int opCrop = 2;
    const int opRot90 = 3;
    const int opRot180 = 4;
    const int opRot270 = 5;
    const int opRot360 = 6;
    const int opFlipH = 7;
    const int opFlipV = 8;
    const int opGrayscale = 9;
    const int opBrightness = 10;
    const int opBlur = 11;
    const int opResize = 12;
    const int opBucketFill = 13;
    const int opReload = 14;
    const int opSave = 15;

    // Sprite cut coordinates from user specification
    const int loadFrameX = 143;
    const int loadFrameY = 31;
    const int loadFrameW = 232;
    const int loadFrameH = 138;

    const int rot90X = 50;
    const int rot90Y = 15;
    const int rot90W = 156;
    const int rot90H = 123;

    const int rot180X = 266;
    const int rot180Y = 12;
    const int rot180W = 165;
    const int rot180H = 125;

    const int rot270X = 492;
    const int rot270Y = 6;
    const int rot270W = 161;
    const int rot270H = 137;

    const int rot360X = 751;
    const int rot360Y = 26;
    const int rot360W = 96;
    const int rot360H = 105;

    const int toolBlurX = 34;
    const int toolBlurY = 27;
    const int toolBlurW = 204;
    const int toolBlurH = 170;

    const int toolBucketX = 490;
    const int toolBucketY = 13;
    const int toolBucketW = 199;
    const int toolBucketH = 198;

    const int toolResizeX = 921;
    const int toolResizeY = 19;
    const int toolResizeW = 247;
    const int toolResizeH = 183;

    const int adjGrayX = 10;
    const int adjGrayY = 0;
    const int adjGrayW = 109;
    const int adjGrayH = 109;

    const int adjBrightX = 186;
    const int adjBrightY = 0;
    const int adjBrightW = 78;
    const int adjBrightH = 113;

    const int adjContrastX = 329;
    const int adjContrastY = 0;
    const int adjContrastW = 125;
    const int adjContrastH = 118;
}
