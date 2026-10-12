#pragma once
#include <iostream>
#include <string>
#include "../../image.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#ifndef STB_IMAGE_STATIC
#define STB_IMAGE_STATIC
#endif
#ifndef CUSTOM_STB_IMAGE_IMPLEMENTED
#define CUSTOM_STB_IMAGE_IMPLEMENTED
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "../stb_image.h"
#pragma GCC diagnostic pop

namespace ReadPath {

    Pixel** readJPEG(const std::string& path, int& width, int& height) {
        if (path.empty()) {
            std::cout << "[Error] Input path is empty.\n";
            return nullptr;
        }

        int w = 0, h = 0, channels = 0;
        unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 3);
        if (!data) {
            std::cout << "[Error] Could not open JPEG image: " << path << "\n";
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
