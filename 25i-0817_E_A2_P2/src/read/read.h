#pragma once
#include <string>
#include "../image.h"
#include "mainLogic/reader.h"

namespace ReadPath {

    Pixel** Read(std::string InputPath, int& width, int& height) {
        return ReadImage(InputPath, width, height);
    }

}
