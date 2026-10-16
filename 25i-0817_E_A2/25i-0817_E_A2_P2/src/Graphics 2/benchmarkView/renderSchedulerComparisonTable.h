#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace GraphicsBenchmark {
    void renderSchedulerComparisonTable(sf::RenderWindow& win, const sf::Font& font, float x, float y, float w, float h) {
        sf::RectangleShape box(sf::Vector2f(w, h));
        box.setPosition(x, y);
        box.setFillColor(sf::Color(15, 20, 28, 240));
        box.setOutlineColor(sf::Color(0, 255, 180));
        box.setOutlineThickness(2.0f);
        win.draw(box);

        sf::Text header;
        header.setFont(font);
        header.setString("SECTION 7.3: 30-JOB SCHEDULER EVALUATION");
        header.setCharacterSize(14);
        header.setFillColor(sf::Color(255, 204, 0));
        header.setPosition(x + 14.0f, y + 10.0f);
        win.draw(header);

        float curY = y + 40.0f;
        sf::Text row0; row0.setFont(font); row0.setString("Metric                          FIFO Mode       Priority Mode   Improvement"); row0.setCharacterSize(12); row0.setFillColor(sf::Color(150, 180, 210)); row0.setPosition(x + 16.0f, curY); win.draw(row0); curY += 24.0f;
        sf::Text row1; row1.setFont(font); row1.setString("Total Jobs Processed            30              30              Identical"); row1.setCharacterSize(12); row1.setFillColor(sf::Color(220, 220, 220)); row1.setPosition(x + 16.0f, curY); win.draw(row1); curY += 20.0f;
        sf::Text row2; row2.setFont(font); row2.setString("Avg Waiting Time (ms)           568.33          526.83          +7.30%"); row2.setCharacterSize(12); row2.setFillColor(sf::Color(220, 220, 220)); row2.setPosition(x + 16.0f, curY); win.draw(row2); curY += 20.0f;
        sf::Text row3; row3.setFont(font); row3.setString("Avg Completion Time (ms)        609.00          567.50          +6.81%"); row3.setCharacterSize(12); row3.setFillColor(sf::Color(220, 220, 220)); row3.setPosition(x + 16.0f, curY); win.draw(row3); curY += 20.0f;
        sf::Text row4; row4.setFont(font); row4.setString("Avg Priority-1 Wait Time        549.17          415.83          24.28% FASTER"); row4.setCharacterSize(12); row4.setFillColor(sf::Color(0, 255, 150)); row4.setPosition(x + 16.0f, curY); win.draw(row4); curY += 28.0f;

        sf::Text footer;
        footer.setFont(font);
        footer.setString("Click 'Toggle Benchmark Table' to close.");
        footer.setCharacterSize(11);
        footer.setFillColor(sf::Color(140, 160, 180));
        footer.setPosition(x + 16.0f, curY);
        win.draw(footer);
    }
}
