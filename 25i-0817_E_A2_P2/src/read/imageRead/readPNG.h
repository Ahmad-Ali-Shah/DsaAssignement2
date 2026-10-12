#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics/Image.hpp>
#include "../../image.h"

namespace ReadPath {

    Pixel** readPNG(const std::string& path, int& width, int& height) {
        if (path.empty()) {
            return nullptr;
        }

        sf::Image img;
        if (!img.loadFromFile(path)) {
            return nullptr;
        }

        width = static_cast<int>(img.getSize().x);
        height = static_cast<int>(img.getSize().y);
        const sf::Uint8* pixels = img.getPixelsPtr();

        Pixel** grid = new Pixel*[height];
        for (int r = 0; r < height; r++) {
            grid[r] = new Pixel[width];
        }

        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                int pos = (r * width + c) * 4;
                grid[r][c].r = static_cast<unsigned int>(pixels[pos]);
                grid[r][c].g = static_cast<unsigned int>(pixels[pos + 1]);
                grid[r][c].b = static_cast<unsigned int>(pixels[pos + 2]);
            }
        }

        return grid;
    }

}
