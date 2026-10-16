#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace GraphicsTheme2 {
    void drawMeter(sf::RenderWindow& win, float x, float y, float w, float h, float ratio, sf::Color barCol, sf::Color bgCol) {
        if (ratio < 0.0f) ratio = 0.0f;
        if (ratio > 1.0f) ratio = 1.0f;

        sf::RectangleShape bg(sf::Vector2f(w, h));
        bg.setPosition(x, y);
        bg.setFillColor(bgCol);
        bg.setOutlineColor(sf::Color(80, 95, 115));
        bg.setOutlineThickness(1.0f);
        win.draw(bg);

        if (ratio > 0.0f) {
            sf::RectangleShape bar(sf::Vector2f(w * ratio, h));
            bar.setPosition(x, y);
            bar.setFillColor(barCol);
            win.draw(bar);
        }
    }
}
