#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "../image.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#ifndef STB_IMAGE_STATIC
#define STB_IMAGE_STATIC
#endif
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"
#pragma GCC diagnostic pop

namespace ReadPath {

    Pixel** ReadImage(std::string InputPath, int& width, int& height) {
        if (InputPath.empty()) {
            std::cout << "[Error] Input path is empty.\n";
            return nullptr;
        }

        bool isPPM = false;
        if (InputPath.length() >= 4) {
            std::string ext = InputPath.substr(InputPath.length() - 4);
            if (ext == ".ppm" || ext == ".PPM") {
                isPPM = true;
            }
        }

        if (isPPM) {
            std::fstream input(InputPath.c_str(), std::ios::in | std::ios::binary);
            if (!input.is_open()) {
                std::cout << "[Error] Could not open file: " << InputPath << "\n";
                return nullptr;
            }

            char Format[2];
            input.read(Format, 2);
            if (Format[0] == 'P' && Format[1] == '6') {
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

        int w = 0, h = 0, channels = 0;
        unsigned char* data = stbi_load(InputPath.c_str(), &w, &h, &channels, 3);
        if (!data) {
            std::cout << "[Error] Could not open image: " << InputPath << "\n";
            return nullptr;
        }

        width = w;
        height = h;

        Pixel** img = new Pixel*[height];
        for (int y = 0; y < height; y++) {
            img[y] = new Pixel[width];
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int idx = (y * width + x) * 3;
                img[y][x].r = static_cast<unsigned int>(data[idx]);
                img[y][x].g = static_cast<unsigned int>(data[idx + 1]);
                img[y][x].b = static_cast<unsigned int>(data[idx + 2]);
            }
        }

        stbi_image_free(data);
        return img;
    }

}
