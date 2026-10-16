#pragma once
#include <string>
#include "../../image.h"
#include "../../read/mainLogic/reader.h"
#include "../../read/mainLogic/deleter.h"

namespace InputPage {

    bool validateAndLoadImage(const std::string& path, Pixel**& outImg, int& outWidth, int& outHeight) {
        if (path.empty()) return false;

        Pixel** loaded = nullptr;
        int w = 0, h = 0;

        loaded = ReadPath::ReadImage(path, w, h);
        if (loaded && w > 0 && h > 0) {
            if (outImg) {
                ReadPath::freeImage(outImg, outHeight);
            }
            outImg = loaded;
            outWidth = w;
            outHeight = h;
            return true;
        }

        return false;
    }

}
