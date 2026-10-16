#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "../../image.h"

namespace ReadPath {

    bool writePPM(const std::string& path, Pixel** img, int width, int height) {

        if (!img || width <= 0 || height <= 0 || path.empty()) {

            return false;
        }

        std::ofstream file(path.c_str(), std::ios::binary);

        if (!file.is_open()) {

            return false;

        }

        file << "P6\n" << width << " " << height << "\n255\n";

        for (int r = 0; r < height; r++) {

            for (int c = 0; c < width; c++) {

                unsigned char rgb[3];

                rgb[0] = static_cast<unsigned char>(img[r][c].r); // for holding proper rgb format 

                rgb[1] = static_cast<unsigned char>(img[r][c].g);

                rgb[2] = static_cast<unsigned char>(img[r][c].b);

                file.write(reinterpret_cast<const char*>(rgb), 3); // re interpriter use for treating constant look there we shall store all the 3 as constant char in the file

            }
        }

        file.close();

        return true;
        
    }

}
