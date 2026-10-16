#pragma once
#include <SFML/Graphics.hpp>

namespace GraphicsTheme {
    void drawBox(sf::RenderWindow& win, float x, float y, float w, float h, sf::Color fill, sf::Color outline, float thickness) {
        sf::RectangleShape box(sf::Vector2f(w, h));
        box.setPosition(x, y);
        box.setFillColor(fill);
        box.setOutlineColor(outline);
        box.setOutlineThickness(thickness);
        win.draw(box);
    }
}
