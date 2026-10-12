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
#include "../HELPER/stb_image.h"
#pragma GCC diagnostic pop

namespace ReadPath {

    Pixel** readJPEG(const std::string& path, int& width, int& height) {
        if (path.empty()) {
            return nullptr;
        }

        int w = 0, h = 0, channels = 0;
        unsigned char* raw = stbi_load(path.c_str(), &w, &h, &channels, 3);
        if (!raw) {
            return nullptr;
        }

        width = w;
        height = h;

        Pixel** grid = new Pixel*[height];
        for (int r = 0; r < height; r++) {
            grid[r] = new Pixel[width];
        }

        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                int pos = (r * width + c) * 3;
                grid[r][c].r = static_cast<unsigned int>(raw[pos]);
                grid[r][c].g = static_cast<unsigned int>(raw[pos + 1]);
                grid[r][c].b = static_cast<unsigned int>(raw[pos + 2]);
            }
        }

        stbi_image_free(raw);
        return grid;
    }

}
