#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics/Image.hpp>
#include "../../image.h"

namespace ReadPath {

    Pixel** readJPEG(const std::string& path, int& width, int& height) {

        if (path.empty()) {

            return nullptr;

        }

        sf::Image img; // make an image in sfml 

        if (!img.loadFromFile(path)) {
             

            // now load that one 

            return nullptr;

        }


        width = static_cast<int>(img.getSize().x); // storing its actual width and height 

        height = static_cast<int>(img.getSize().y);

        const sf::Uint8* pixels = img.getPixelsPtr(); // since colour store the Uint of 8 byte as a value and generate relevent pixel from it 

        Pixel** grid = new Pixel*[height];

        for (int r = 0; r < height; r++) {

            grid[r] = new Pixel[width];

        }

        for (int r = 0; r < height; r++) {

            for (int c = 0; c < width; c++) {

                int pos = (r * width + c) * 4;// since WE ARE STORIING THE  THE VALUE AS AN ARRAY OF 4 SO EACH AFTER 4 CONZECTIVE ITEMS BE SHOWN THERE 


                grid[r][c].r = static_cast<unsigned int>(pixels[pos]);// SO THAT NEXT ONE IS NOT TREATED LIKE GREEN OR BLUE 

                grid[r][c].g = static_cast<unsigned int>(pixels[pos + 1]);

                grid[r][c].b = static_cast<unsigned int>(pixels[pos + 2]);

            }
        }

        return grid;
    }

}
