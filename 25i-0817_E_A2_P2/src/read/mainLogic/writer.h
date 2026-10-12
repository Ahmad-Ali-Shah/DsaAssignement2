#pragma once
#include <string>
#include "../../image.h"
#include "../imageWrite/writePPM.h"
#include "../imageWrite/writePNG.h"
#include "../imageWrite/writeJPEG.h"

namespace ReadPath {

    bool WriteImage(std::string OutputPath, Pixel** img, int width, int height, bool asPPM = false) {
        if (!img || width <= 0 || height <= 0 || OutputPath.empty()) {
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

        if (asPPM || ext == ".ppm") {
            return writePPM(OutputPath, img, width, height);
        }
        if (ext == ".png") {
            return writePNG(OutputPath, img, width, height);
        }
        if (ext == ".jpg" || ext5 == ".jpeg") {
            return writeJPEG(OutputPath, img, width, height);
        }

        return writePNG(OutputPath, img, width, height);
    }

}
