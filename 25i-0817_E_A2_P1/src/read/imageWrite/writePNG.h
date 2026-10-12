#pragma once
#include <iostream>
#include <string>
#include "../../image.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#ifndef STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_STATIC
#endif
#ifndef CUSTOM_STB_IMAGE_WRITE_IMPLEMENTED
#define CUSTOM_STB_IMAGE_WRITE_IMPLEMENTED
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif
#include "../stb_image_write.h"
#pragma GCC diagnostic pop

namespace ReadPath {

    bool writePNG(const std::string& path, Pixel** img, int width, int height) {
        if (!img || width <= 0 || height <= 0 || path.empty()) {
            std::cout << "[Error] Invalid image data or output path.\n";
            return false;
        }

        unsigned char* buffer = new unsigned char[width * height * 3];
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int idx = (y * width + x) * 3;
                buffer[idx] = static_cast<unsigned char>(img[y][x].r);
                buffer[idx + 1] = static_cast<unsigned char>(img[y][x].g);
                buffer[idx + 2] = static_cast<unsigned char>(img[y][x].b);
            }
        }

        int res = stbi_write_png(path.c_str(), width, height, 3, buffer, width * 3);
        delete[] buffer;
        return res != 0;
    }

}
