#pragma once
#include "../../image.h"
#include "../blur/blur.h"

namespace FrobeniusMatrixInnerProductForBlurr {
    void applyBlur(Pixel** img, int width, int height) {
        if (!img || width <= 0 || height <= 0) return;

        Pixel** temp = new Pixel*[height];
        for (int y = 0; y < height; y++) {
            temp[y] = new Pixel[width];
        }

        double patchR[3][3], patchG[3][3], patchB[3][3];

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int py = clampCoord(y + dy, height);
                        int px = clampCoord(x + dx, width);
                        patchR[dy + 1][dx + 1] = static_cast<double>(img[py][px].r);
                        patchG[dy + 1][dx + 1] = static_cast<double>(img[py][px].g);
                        patchB[dy + 1][dx + 1] = static_cast<double>(img[py][px].b);
                    }
                }
                blurPixel(patchR, patchG, patchB, temp[y][x].r, temp[y][x].g, temp[y][x].b);
            }
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                img[y][x] = temp[y][x];
            }
            delete[] temp[y];
        }
        delete[] temp;
    }
}
