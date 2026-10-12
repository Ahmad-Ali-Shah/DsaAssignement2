#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "../../image.h"

namespace ReadPath {

    bool writePPM(const std::string& path, Pixel** img, int width, int height) {
        if (!img || width <= 0 || height <= 0 || path.empty()) {
            std::cout << "[Error] Invalid image data or output path.\n";
            return false;
        }

        std::fstream output(path.c_str(), std::ios::out | std::ios::binary);
        if (!output.is_open()) {
            std::cout << "[Error] Could not create file: " << path << "\n";
            return false;
        }

        output << "P6\n" << width << " " << height << "\n255\n";

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned char rgb[3];
                rgb[0] = static_cast<unsigned char>(img[y][x].r);
                rgb[1] = static_cast<unsigned char>(img[y][x].g);
                rgb[2] = static_cast<unsigned char>(img[y][x].b);
                output.write(reinterpret_cast<const char*>(rgb), 3);
            }
        }

        output.close();
        return true;
    }

}
