#pragma once
#include "../../image.h"
#include "rotation.h"

namespace rotateObject {
    Pixel** applyRotate(Pixel** img, int& width, int& height, int angle) {
        if (!img || width <= 0 || height <= 0) return img;
        int normAngle = angle % 360;
        if (normAngle < 0) normAngle += 360;

        if (normAngle == 0) return img;

        int newW = width;
        int newH = height;
        if (normAngle == 90 || normAngle == 270) {
            newW = height;
            newH = width;
        }

        Pixel** rotated = new Pixel*[newH];
        for (int y = 0; y < newH; y++) {
            rotated[y] = new Pixel[newW];
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rx = x;
                int ry = y;
                rotate(rx, ry, height, width, normAngle);
                if (rx >= 0 && rx < newW && ry >= 0 && ry < newH) {
                    rotated[ry][rx] = img[y][x];
                }
            }
        }

        for (int y = 0; y < height; y++) {
            delete[] img[y];
        }
        delete[] img;

        width = newW;
        height = newH;
        return rotated;
    }
}
