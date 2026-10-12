#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics/Image.hpp>
#include "../../image.h"

namespace ReadPath {

    bool writeJPEG(const std::string& path, Pixel** img, int width, int height, int quality = 95) {
        (void)quality;
        if (!img || width <= 0 || height <= 0 || path.empty()) {
            return false;
        }

        sf::Image sfImg;
        sfImg.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height));

        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                sf::Color clr(
                    static_cast<sf::Uint8>(img[r][c].r),
                    static_cast<sf::Uint8>(img[r][c].g),
                    static_cast<sf::Uint8>(img[r][c].b),
                    255
                );
                sfImg.setPixel(static_cast<unsigned int>(c), static_cast<unsigned int>(r), clr);
            }
        }

        return sfImg.saveToFile(path);
    }

}
