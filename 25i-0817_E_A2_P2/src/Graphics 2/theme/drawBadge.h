#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace GraphicsTheme2 {
    void drawBadge(sf::RenderWindow& win, const sf::Font& font, float x, float y, const std::string& label, sf::Color bgCol, sf::Color textCol) {
        float padding = 6.0f;
        float w = label.length() * 7.5f + padding * 2.0f;
        float h = 18.0f;

        sf::RectangleShape badge(sf::Vector2f(w, h));
        badge.setPosition(x, y);
        badge.setFillColor(bgCol);
        badge.setOutlineColor(sf::Color(255, 255, 255, 50));
        badge.setOutlineThickness(1.0f);
        win.draw(badge);

        sf::Text text;
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(11);
        text.setFillColor(textCol);
        text.setPosition(x + padding, y + 2.0f);
        win.draw(text);
    }
}
