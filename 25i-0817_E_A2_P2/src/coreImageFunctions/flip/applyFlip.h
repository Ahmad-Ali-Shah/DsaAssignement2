#pragma once
#include "../../image.h"
#include "flip.h"

namespace flipAxis {
    void applyFlipHorizontal(Pixel** img, int width, int height) {

        if (!img || width <= 0 || height <= 0) 
        return;

        for (int y = 0; y < height; y++) {

            for (int x = 0; x < width / 2; x++) {

                Pixel temp = img[y][x];

                img[y][x] = img[y][width - 1 - x];

                img[y][width - 1 - x] = temp;

            }

        }

    }


    void applyFlipVertical(Pixel** img, int width, int height) {

        if (!img || width <= 0 || height <= 0)
         return;

        for (int y = 0; y < height / 2; y++) {

            for (int x = 0; x < width; x++) {

                Pixel temp = img[y][x];

                img[y][x] = img[height - 1 - y][x];

                img[height - 1 - y][x] = temp;
                
            }
        }
    }
}
