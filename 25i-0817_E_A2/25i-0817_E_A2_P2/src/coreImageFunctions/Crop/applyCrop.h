#pragma once
#include "../../image.h"
#include "crop.h"

namespace myCrop {
    Pixel** applyCrop(Pixel** img, int& width, int& height, int startX, int startY, int cropW, int cropH) {

        if (!img || width <= 0 || height <= 0) 
        return img;
        if (startX < 0) 
        startX = 0;
        if (startY < 0)
         startY = 0;
        if (startX + cropW > width) 
        cropW = width - startX;
        if (startY + cropH > height)
         cropH = height - startY;
        if (cropW <= 0 || cropH <= 0) 
        return img;

        Pixel** cropped = new Pixel*[cropH];

        for (int y = 0; y < cropH; y++) {

            cropped[y] = new Pixel[cropW];

            for (int x = 0; x < cropW; x++) {

                int ox = x;

                int oy = y;

                crop(ox, oy, startX, startY);

                cropped[y][x] = img[oy][ox];

            }

        }

        for (int y = 0; y < height; y++) {

            delete[] img[y];

        }

        delete[] img;


        width = cropW;

        height = cropH;

        return cropped;
        
    }
}
