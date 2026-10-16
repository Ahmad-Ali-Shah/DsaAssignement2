#pragma once
#include "../../image.h"
#include "resize.h"

namespace scaling {
    Pixel** applyResize(Pixel** img, int& width, int& height, int targetW, int targetH) {
        if (!img || width <= 0 || height <= 0 || targetW <= 0 || targetH <= 0) return img;

        Pixel** resized = new Pixel*[targetH];
        for (int y = 0; y < targetH; y++) {
            resized[y] = new Pixel[targetW];
            for (int x = 0; x < targetW; x++) {
                int srcX = x;
                int srcY = y;
                scale(targetW, targetH, width, height, srcX, srcY);
                resized[y][x] = img[srcY][srcX];
            }
        }

        for (int y = 0; y < height; y++) {
            delete[] img[y];
        }
        delete[] img;

        width = targetW;
        height = targetH;
        return resized;
    }
}
