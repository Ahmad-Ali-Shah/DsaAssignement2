#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics/Image.hpp>
#include "../../image.h"

namespace ReadPath {

    // USIING TH IMAGE SUB LIBRARY TO READ PNG

    bool writePNG(const std::string& path, Pixel** img, int width, int height) {

        if (!img || width <= 0 || height <= 0 || path.empty()) {

            return false;

        }


        sf::Image sfImg; // CREATE AN IMAGE OBJECT 

        sfImg.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height)); // PASSING HEIGHT AND WIDTH SO IT CREATE A SAM WIDTH AND HEIGHT IMAGE 

        for (int r = 0; r < height; r++) {

            for (int c = 0; c < width; c++) {

                sf::Color clr( static_cast<sf::Uint8>(img[r][c].r), static_cast<sf::Uint8>(img[r][c].g),static_cast<sf::Uint8>(img[r][c].b),  255  );


                // SINCE COLOUR TOOK 4 THINGS IN SFML
            // Color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha = (sf::Uint8)255U)
            // as prrimeter so castiing each and every value to Uint 8 so that red , green and blue and alpha that's projection be shown in one piixel and same i did above


                sfImg.setPixel(static_cast<unsigned int>(c), static_cast<unsigned int>(r), clr); // place the pixel at a specific position 

            }

        }


        return sfImg.saveToFile(path);

    }
    

}
