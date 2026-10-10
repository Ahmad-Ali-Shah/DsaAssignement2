#pragma once
#include "../image.h"

namespace ReadPath {

    void freeImage(Pixel** img, int height) {
        if (!img) return;
        for (int y = 0; y < height; y++) {
            delete[] img[y];
        }
        delete[] img;
    }

}
