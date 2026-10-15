#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>


#include <string>

namespace GraphicsAnimator {

    //////////////////////////////////////

    // for loading sprite

    ///////////////////////////////////

    bool loadSpriteSheet(sf::Texture& tex, const std::string& path) {

        if (!tex.loadFromFile(path)) {

            std::cout << "[UI Warning] Could not load sprite sheet from: " << path << "\n";

            return false;

        }

        return true;
        
    }
}
