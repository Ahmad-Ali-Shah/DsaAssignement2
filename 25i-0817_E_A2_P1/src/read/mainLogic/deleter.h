#pragma once
#include "../../image.h"

namespace ReadPath {

    void freeImage(Pixel** img, int height) {
        if (!img) return;
        for (int r = 0; r < height; r++) {
            delete[] img[r];
        }
        delete[] img;
    }

}
