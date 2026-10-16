#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

namespace GraphicsTheme {
    bool loadFont(sf::Font& font, const string& path) {
        if (!font.loadFromFile(path)) {
            cout << "[UI Warning] Could not load font from: " << path << "\n";
            return false;
        }
        return true;
    }
}
