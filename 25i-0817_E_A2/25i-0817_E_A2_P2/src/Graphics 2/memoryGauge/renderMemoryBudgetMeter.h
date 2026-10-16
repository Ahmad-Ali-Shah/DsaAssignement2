#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../../history/history.h"
#include "../theme/drawMeter.h"
#include "../theme/drawBadge.h"

namespace GraphicsMemory {
    void renderMemoryBudgetMeter(sf::RenderWindow& win, const sf::Font& font, float x, float y, float w, float h, const HistoryManager& history) {
        sf::RectangleShape box(sf::Vector2f(w, h));
        box.setPosition(x, y);
        box.setFillColor(sf::Color(18, 22, 28));
        box.setOutlineColor(sf::Color(45, 55, 70));
        box.setOutlineThickness(1.0f);
        win.draw(box);

        unsigned int used = history.getCurrentMemoryUsage();
        unsigned int budget = history.getMemoryBudget();
        float ratio = (budget > 0) ? (static_cast<float>(used) / static_cast<float>(budget)) : 0.0f;

        sf::Color barCol = (ratio > 0.85f) ? sf::Color(255, 60, 60) : sf::Color(0, 204, 255);
        GraphicsTheme2::drawMeter(win, x + 10.0f, y + 26.0f, w - 20.0f, 14.0f, ratio, barCol, sf::Color(30, 35, 45));

        sf::Text label;
        label.setFont(font);
        label.setString("MEMORY-AWARE HISTORY BUDGET (SECTION 7.1)");
        label.setCharacterSize(11);
        label.setFillColor(sf::Color(255, 204, 0));
        label.setPosition(x + 10.0f, y + 8.0f);
        win.draw(label);

        std::string statStr = std::to_string(used / 1024) + " KB / " + std::to_string(budget / 1024) + " KB (" + std::to_string(static_cast<int>(ratio * 100)) + "%)";
        sf::Text stats;
        stats.setFont(font);
        stats.setString(statStr);
        stats.setCharacterSize(11);
        stats.setFillColor(sf::Color(220, 220, 220));
        stats.setPosition(x + 10.0f, y + 46.0f);
        win.draw(stats);

        int discarded = history.getDiscardedCount();
        if (discarded > 0) {
            std::string discStr = "Evicted: " + std::to_string(discarded) + " via removeBottom()";
            GraphicsTheme2::drawBadge(win, font, x + w - 170.0f, y + 44.0f, discStr, sf::Color(120, 40, 40), sf::Color(255, 255, 255));
        }
    }
}
