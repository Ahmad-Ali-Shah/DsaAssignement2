#pragma once
#include <SFML/Graphics.hpp>
#include "../../image.h"

namespace GraphicsCanvas {
    bool createTextureFromPixels(sf::Texture& tex, Pixel** img, int width, int height) {

        if (!img || width <= 0 || height <= 0)
         return false;


        sf::Uint8* pixels = new sf::Uint8[width * height * 4];

        for (int y = 0; y < height; y++) {

            for (int x = 0; x < width; x++) {

                int idx = (y * width + x) * 4;

                pixels[idx] = static_cast<sf::Uint8>(img[y][x].r);

                pixels[idx + 1] = static_cast<sf::Uint8>(img[y][x].g);

                pixels[idx + 2] = static_cast<sf::Uint8>(img[y][x].b);

                pixels[idx + 3] = 255;

            }

        }

        sf::Image sfImg;

        sfImg.create(width, height, pixels);

        delete[] pixels;

        return tex.loadFromImage(sfImg);

    }
    
}

