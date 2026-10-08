#pragma once
#include "../../image.h"
#include "../greyScale/greyScale.h"

namespace MygreyScale {
    void applyGrayscale(Pixel** img, int width, int height) {
        if (!img || width <= 0 || height <= 0) return;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                greyScale(img[y][x].r, img[y][x].g, img[y][x].b);
            }
        }
    }
}
