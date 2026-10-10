#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../theme/drawBox.h"
#include "../theme/drawText.h"

namespace GraphicsToolbar {
    void renderToolButton(sf::RenderWindow& win, const sf::Font& font, float x, float y, float w, float h, const std::string& label, bool hovered, sf::Color baseCol) {
        sf::Color bg = hovered ? sf::Color(baseCol.r + 25, baseCol.g + 25, baseCol.b + 25) : baseCol;
        sf::Color outline = hovered ? sf::Color(255, 204, 0) : sf::Color(80, 90, 110);
        GraphicsTheme::drawBox(win, x, y, w, h, bg, outline, 1.0f);
        GraphicsTheme::drawText(win, font, label, x + 8.0f, y + 6.0f, 13, sf::Color(240, 240, 240));
    }
}
