#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../theme/drawBox.h"
#include "../theme/drawText.h"

namespace GraphicsPipeline {
    void renderJobCard(sf::RenderWindow& win, const sf::Font& font, float x, float y, float w, float h, int id, const std::string& name, bool isFront) {
        sf::Color bg = isFront ? sf::Color(35, 75, 55) : sf::Color(32, 40, 52);
        sf::Color border = isFront ? sf::Color(0, 255, 150) : sf::Color(70, 85, 105);
        GraphicsTheme::drawBox(win, x, y, w, h, bg, border, 1.0f);
        std::string title = "#" + std::to_string(id) + " " + name;
        GraphicsTheme::drawText(win, font, title, x + 6.0f, y + 6.0f, 12, sf::Color(240, 240, 240));
        if (isFront) {
            GraphicsTheme::drawText(win, font, "[FRONT]", x + w - 50.0f, y + 6.0f, 10, sf::Color(0, 255, 150));
        }
    }
}
