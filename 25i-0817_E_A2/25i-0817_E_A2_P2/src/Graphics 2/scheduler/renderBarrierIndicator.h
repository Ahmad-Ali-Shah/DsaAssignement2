#pragma once
#include <SFML/Graphics.hpp>

namespace GraphicsScheduler {
    void renderBarrierIndicator(sf::RenderWindow& win, float x, float y, float h) {
        sf::RectangleShape line(sf::Vector2f(2.0f, h));
        line.setPosition(x, y);
        line.setFillColor(sf::Color(255, 204, 0));
        win.draw(line);
    }
}
