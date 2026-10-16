#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "visConstants.h"

namespace VisPage {

    struct VisButtonDrawer {
        sf::RenderWindow& window;
        const sf::Font& font;
        float startX;
        float panelW;
        float& curY;
        float mouseX;
        float mouseY;

        void operator()(sf::FloatRect& r, const std::string& label, sf::Color cNormal, sf::Color cHover) const {
            r = sf::FloatRect(startX, curY, panelW, 46.0f);
            bool hovered = r.contains(mouseX, mouseY);
            sf::RectangleShape b(sf::Vector2f(panelW, 46.0f));
            b.setPosition(startX, curY);
            b.setFillColor(hovered ? cHover : cNormal);
            b.setOutlineColor(hovered ? sf::Color(255, 235, 80) : sf::Color(90, 155, 225, 200));
            b.setOutlineThickness(hovered ? 2.5f : 1.5f);
            window.draw(b);

            sf::Text t;
            t.setFont(font);
            t.setString(label);
            t.setCharacterSize(18);
            t.setFillColor(hovered ? sf::Color(255, 235, 80) : sf::Color(240, 245, 255));
            sf::FloatRect tb = t.getLocalBounds();
            t.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
            t.setPosition(startX + panelW / 2.0f, curY + 23.0f);
            window.draw(t);

            curY += 58.0f;
        }
    };

    void renderVisControls(sf::RenderWindow& window, const sf::Font& font, float mouseX, float mouseY, VisConstants::VisButtonRects& rects) {
        float winW = static_cast<float>(window.getSize().x);
        float startX = winW - 305.0f;
        float curY = 32.0f;
        float panelW = 280.0f;

        // Section Title: DATA STRUCTURES
        sf::Text title;
        title.setFont(font);
        title.setString("DATA STRUCTURE VIS");
        title.setCharacterSize(22);
        title.setFillColor(sf::Color(255, 228, 50));
        title.setPosition(startX + 10.0f, curY);
        window.draw(title);
        curY += 38.0f;

        VisButtonDrawer drawVisBtn{window, font, startX, panelW, curY, mouseX, mouseY};

        // 1. Show Stack Button (Blue)
        drawVisBtn(rects.showStackBtn, "SHOW STACK (LIFO)", sf::Color(18, 55, 110, 235), sf::Color(30, 90, 180, 255));

        // 2. Show Queue Button (Cyan-blue)
        drawVisBtn(rects.showQueueBtn, "SHOW QUEUE (FIFO)", sf::Color(14, 75, 75, 235), sf::Color(25, 120, 120, 255));

        // 3. Animate All Operations (Stack & Queue pop/push animation)
        drawVisBtn(rects.animDataBtn, "ANIMATE OPERATIONS", sf::Color(80, 30, 105, 235), sf::Color(130, 45, 170, 255));

        // 4. Animate Image Transitions (Full Conversion animation)
        drawVisBtn(rects.animImageBtn, "ANIMATE PIPELINE", sf::Color(25, 80, 45, 235), sf::Color(40, 130, 75, 255));

        // 5. Back to Main Menu Button (Burgundy)
        drawVisBtn(rects.backBtn, "<-- BACK TO MAIN MENU", sf::Color(105, 30, 40, 235), sf::Color(155, 45, 60, 255));
    }

}
