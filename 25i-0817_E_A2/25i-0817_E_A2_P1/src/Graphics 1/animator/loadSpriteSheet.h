#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>


#include <string>

using namespace std;

namespace GraphicsAnimator {
    bool loadSpriteSheet(sf::Texture& tex, const string& path) {
        if (!tex.loadFromFile(path)) {
            cout << "[UI Warning] Could not load sprite sheet from: " << path << "\n";
            return false;
        }
        return true;
    }
}
