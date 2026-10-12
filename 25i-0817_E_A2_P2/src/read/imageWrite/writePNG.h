#pragma once
#include <iostream>
#include <string>
#include "../../image.h"
#include "../HELPER/stb_core.h"

namespace ReadPath {

    bool writePNG(const std::string& path, Pixel** img, int width, int height) {
        if (!img || width <= 0 || height <= 0 || path.empty()) {
            return false;
        }

        unsigned char* buf = new unsigned char[width * height * 3];
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                int pos = (r * width + c) * 3;
                buf[pos] = static_cast<unsigned char>(img[r][c].r);
                buf[pos + 1] = static_cast<unsigned char>(img[r][c].g);
                buf[pos + 2] = static_cast<unsigned char>(img[r][c].b);
            }
        }

        int ok = stbi_write_png(path.c_str(), width, height, 3, buf, width * 3);
        delete[] buf;
        return ok != 0;
    }

}
