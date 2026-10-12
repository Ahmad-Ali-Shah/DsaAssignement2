#pragma once
#include <string>
#include "../image.h"
#include "imageRead/readPPM.h"
#include "imageRead/readPNG.h"
#include "imageRead/readJPEG.h"

namespace ReadPath {

    Pixel** ReadImage(std::string InputPath, int& width, int& height) {
        if (InputPath.empty()) {
            std::cout << "[Error] Input path is empty.\n";
            return nullptr;
        }

        std::string ext = "";
        if (InputPath.length() >= 4) {
            ext = InputPath.substr(InputPath.length() - 4);
            for (size_t i = 0; i < ext.length(); i++) {
                if (ext[i] >= 'A' && ext[i] <= 'Z') {
                    ext[i] = static_cast<char>(ext[i] + 32);
                }
            }
        }
        std::string ext5 = "";
        if (InputPath.length() >= 5) {
            ext5 = InputPath.substr(InputPath.length() - 5);
            for (size_t i = 0; i < ext5.length(); i++) {
                if (ext5[i] >= 'A' && ext5[i] <= 'Z') {
                    ext5[i] = static_cast<char>(ext5[i] + 32);
                }
            }
        }

        if (ext == ".ppm") {
            return readPPM(InputPath, width, height);
        }
        if (ext == ".png") {
            return readPNG(InputPath, width, height);
        }
        if (ext == ".jpg" || ext5 == ".jpeg") {
            return readJPEG(InputPath, width, height);
        }

        Pixel** img = readPNG(InputPath, width, height);
        if (img) return img;
        img = readJPEG(InputPath, width, height);
        if (img) return img;
        return readPPM(InputPath, width, height);
    }

}
