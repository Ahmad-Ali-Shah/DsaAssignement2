#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "../image.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#ifndef STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_STATIC
#endif
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif
#include "stb_image_write.h"
#pragma GCC diagnostic pop

namespace ReadPath {

    bool WriteImage(std::string OutputPath, Pixel** img, int width, int height, bool asPPM = false) {
        if (!img || width <= 0 || height <= 0 || OutputPath.empty()) {
            std::cout << "[Error] Invalid image data or output path.\n";
            return false;
        }

        std::string ext = "";
        if (OutputPath.length() >= 4) {
            ext = OutputPath.substr(OutputPath.length() - 4);
            for (size_t i = 0; i < ext.length(); i++) {
                if (ext[i] >= 'A' && ext[i] <= 'Z') {
                    ext[i] = static_cast<char>(ext[i] + 32);
                }
            }
        }
        std::string ext5 = "";
        if (OutputPath.length() >= 5) {
            ext5 = OutputPath.substr(OutputPath.length() - 5);
            for (size_t i = 0; i < ext5.length(); i++) {
                if (ext5[i] >= 'A' && ext5[i] <= 'Z') {
                    ext5[i] = static_cast<char>(ext5[i] + 32);
                }
            }
        }

        if (ext == ".png") {
            unsigned char* buffer = new unsigned char[width * height * 3];
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int idx = (y * width + x) * 3;
                    buffer[idx] = static_cast<unsigned char>(img[y][x].r);
                    buffer[idx + 1] = static_cast<unsigned char>(img[y][x].g);
                    buffer[idx + 2] = static_cast<unsigned char>(img[y][x].b);
                }
            }
            int res = stbi_write_png(OutputPath.c_str(), width, height, 3, buffer, width * 3);
            delete[] buffer;
            return res != 0;
        }

        if (ext == ".jpg" || ext5 == ".jpeg") {
            unsigned char* buffer = new unsigned char[width * height * 3];
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int idx = (y * width + x) * 3;
                    buffer[idx] = static_cast<unsigned char>(img[y][x].r);
                    buffer[idx + 1] = static_cast<unsigned char>(img[y][x].g);
                    buffer[idx + 2] = static_cast<unsigned char>(img[y][x].b);
                }
            }
            int res = stbi_write_jpg(OutputPath.c_str(), width, height, 3, buffer, 95);
            delete[] buffer;
            return res != 0;
        }

        std::fstream output(OutputPath.c_str(), std::ios::out | std::ios::binary);
        if (!output.is_open()) {
            std::cout << "[Error] Could not create file: " << OutputPath << "\n";
            return false;
        }

        if (asPPM || ext == ".ppm") {
            output << "P6\n" << width << " " << height << "\n255\n";
        }

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
