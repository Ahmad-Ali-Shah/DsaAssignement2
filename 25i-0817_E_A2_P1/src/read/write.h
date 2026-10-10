#pragma once
#include <string>
#include "../image.h"
#include "writeImage.h"

namespace ReadPath {

    bool Write(std::string OutputPath, Pixel** img, int width, int height, bool asPPM = true) {
        return WriteImage(OutputPath, img, width, height, asPPM);
    }

}
