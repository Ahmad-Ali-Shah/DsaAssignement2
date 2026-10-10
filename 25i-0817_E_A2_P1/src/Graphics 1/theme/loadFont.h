#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GraphicsTheme {
    bool loadFont(sf::Font& font, const std::string& path) {
        if (!font.loadFromFile(path)) {
            std::cout << "[UI Warning] Could not load font from: " << path << "\n";
            return false;
        }
        return true;
    }
}
