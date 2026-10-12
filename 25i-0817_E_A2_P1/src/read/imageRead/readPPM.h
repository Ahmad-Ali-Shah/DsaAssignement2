#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "../../image.h"

namespace ReadPath {

    Pixel** readPPM(const std::string& path, int& width, int& height) {
        std::fstream input(path.c_str(), std::ios::in | std::ios::binary);
        if (!input.is_open()) {
            std::cout << "[Error] Could not open PPM file: " << path << "\n";
            return nullptr;
        }

        char format[2];
        input.read(format, 2);
        if (format[0] == 'P' && format[1] == '6') {
            int fileW = 0, fileH = 0, maxVal = 255;
            input >> fileW >> fileH >> maxVal;
            char whitespace;
            input.read(&whitespace, 1);
            if (fileW > 0 && fileH > 0) {
                width = fileW;
                height = fileH;
            }
        } else {
            input.seekg(0, std::ios::beg);
        }

        if (width <= 0 || height <= 0) {
            input.close();
            return nullptr;
        }

        Pixel** img = new Pixel*[height];
        for (int y = 0; y < height; y++) {
            img[y] = new Pixel[width];
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned char rgb[3];
                input.read(reinterpret_cast<char*>(rgb), 3);
                img[y][x].r = static_cast<unsigned int>(rgb[0]);
                img[y][x].g = static_cast<unsigned int>(rgb[1]);
                img[y][x].b = static_cast<unsigned int>(rgb[2]);
            }
        }

        input.close();
        return img;
    }

}
