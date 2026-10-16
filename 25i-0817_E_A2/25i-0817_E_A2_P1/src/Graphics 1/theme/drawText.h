#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace GraphicsTheme {
    void drawText(sf::RenderWindow& win, const sf::Font& font, const std::string& str, float x, float y, unsigned int size, sf::Color col) {
        sf::Text text;
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(size);
        text.setFillColor(col);
        text.setPosition(x, y);
        win.draw(text);
    }
}
