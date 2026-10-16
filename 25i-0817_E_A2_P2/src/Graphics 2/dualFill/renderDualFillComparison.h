#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace GraphicsDualFill {
    void renderDualFillComparison(sf::RenderWindow& win, const sf::Font& font, float x, float y, float w, float h, int animFrame) {
        sf::RectangleShape box(sf::Vector2f(w, h));
        box.setPosition(x, y);
        box.setFillColor(sf::Color(16, 20, 26, 245));
        box.setOutlineColor(sf::Color(0, 204, 255));
        box.setOutlineThickness(2.0f);
        win.draw(box);

        sf::Text header;
        header.setFont(font);
        header.setString("SECTION 7.5: SIDE-BY-SIDE BUCKET FILL TRAVERSAL COMPARISON");
        header.setCharacterSize(14);
        header.setFillColor(sf::Color(255, 204, 0));
        header.setPosition(x + 14.0f, y + 10.0f);
        win.draw(header);

        float halfW = (w - 40.0f) / 2.0f;
        float canvasH = h - 60.0f;

        // Left: Stack-based DFS
        sf::RectangleShape leftBox(sf::Vector2f(halfW, canvasH));
        leftBox.setPosition(x + 15.0f, y + 40.0f);
        leftBox.setFillColor(sf::Color(25, 28, 35));
        leftBox.setOutlineColor(sf::Color(255, 120, 60));
        leftBox.setOutlineThickness(1.0f);
        win.draw(leftBox);

        sf::Text leftLabel;
        leftLabel.setFont(font);
        leftLabel.setString("STACK-BASED (Deep Fill)");
        leftLabel.setCharacterSize(12);
        leftLabel.setFillColor(sf::Color(255, 140, 80));
        leftLabel.setPosition(x + 20.0f, y + 46.0f);
        win.draw(leftLabel);

        // Right: Queue-based
        sf::RectangleShape rightBox(sf::Vector2f(halfW, canvasH));
        rightBox.setPosition(x + 25.0f + halfW, y + 40.0f);
        rightBox.setFillColor(sf::Color(25, 28, 35));
        rightBox.setOutlineColor(sf::Color(60, 180, 255));
        rightBox.setOutlineThickness(1.0f);
        win.draw(rightBox);

        sf::Text rightLabel;
        rightLabel.setFont(font);
        rightLabel.setString("QUEUE-BASED (Radial Fill)");
        rightLabel.setCharacterSize(12);
        rightLabel.setFillColor(sf::Color(100, 200, 255));
        rightLabel.setPosition(x + 30.0f + halfW, y + 46.0f);
        win.draw(rightLabel);

        // Animated traversal patterns
        int steps = animFrame % 40;
        // DFS pattern (snake/branch)
        for (int i = 0; i < steps * 3; i++) {
            float px = x + 30.0f + (i % 20) * 12.0f;
            float py = y + 80.0f + (i / 20) * 12.0f;
            sf::RectangleShape dot(sf::Vector2f(10.0f, 10.0f));
            dot.setPosition(px, py);
            dot.setFillColor(sf::Color(255, 120, 60));
            win.draw(dot);
        }

        // BFS pattern (expanding circles)
        float cx = x + 25.0f + halfW + halfW / 2.0f;
        float cy = y + 40.0f + canvasH / 2.0f;
        for (int r = 1; r <= (steps / 2); r++) {
            sf::CircleShape ring(r * 12.0f);
            ring.setOrigin(r * 12.0f, r * 12.0f);
            ring.setPosition(cx, cy);
            ring.setFillColor(sf::Color(0, 0, 0, 0));
            ring.setOutlineColor(sf::Color(60, 180, 255));
            ring.setOutlineThickness(2.0f);
            win.draw(ring);
        }
    }
}
