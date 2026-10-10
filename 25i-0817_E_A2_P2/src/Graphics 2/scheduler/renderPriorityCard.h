#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../theme/drawBadge.h"

namespace GraphicsScheduler {
    void renderPriorityCard(sf::RenderWindow& win, const sf::Font& font, float x, float y, float w, float h, int id, const std::string& name, int priority, bool isBarrier) {
        sf::Color bg = sf::Color(32, 40, 52);
        sf::Color border = sf::Color(70, 85, 105);

        if (priority == 1) { bg = sf::Color(65, 30, 30); border = sf::Color(255, 80, 80); }
        else if (priority == 2) { bg = sf::Color(30, 45, 65); border = sf::Color(80, 160, 255); }
        else if (priority == 3) { bg = sf::Color(30, 55, 40); border = sf::Color(80, 220, 120); }
        else if (priority == 4) { bg = sf::Color(55, 35, 65); border = sf::Color(200, 100, 255); }

        sf::RectangleShape box(sf::Vector2f(w, h));
        box.setPosition(x, y);
        box.setFillColor(bg);
        box.setOutlineColor(border);
        box.setOutlineThickness(1.0f);
        win.draw(box);

        sf::Text title;
        title.setFont(font);
        title.setString("#" + std::to_string(id) + " " + name);
        title.setCharacterSize(12);
        title.setFillColor(sf::Color(240, 240, 240));
        title.setPosition(x + 6.0f, y + 4.0f);
        win.draw(title);

        std::string pStr = "P" + std::to_string(priority);
        GraphicsTheme2::drawBadge(win, font, x + w - 30.0f, y + 4.0f, pStr, border, sf::Color(0, 0, 0));

        if (isBarrier) {
            GraphicsTheme2::drawBadge(win, font, x + 6.0f, y + 20.0f, "BARRIER", sf::Color(255, 204, 0), sf::Color(0, 0, 0));
        }
    }
}
