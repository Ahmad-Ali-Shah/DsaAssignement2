#pragma once
#include "../../image.h"
#include "../brightness/brightness.h"

namespace MyBrightness {
    void applyBrightness(Pixel** img, int width, int height, double delta) {
        if (!img || width <= 0 || height <= 0) return;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                brightness(img[y][x].r, img[y][x].g, img[y][x].b, delta);
            }
        }
    }
}
