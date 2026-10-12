#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "selectionConstants.h"

namespace SelectionPage {

    void renderSelectionOptions(sf::RenderWindow& window, const sf::Font& font, int hoveredChoice, sf::FloatRect& outRect1, sf::FloatRect& outRect2) {
        float winW = static_cast<float>(window.getSize().x);

        float opt1Y = 360.0f;
        float opt2Y = 470.0f;
        float boxW = 556.0f;
        float boxH = 64.0f;
        float boxX = (winW - boxW) / 2.0f;

        // Card 1: -> IMAGE LAB
        outRect1 = sf::FloatRect(boxX, opt1Y - boxH / 2.0f, boxW, boxH);
        sf::RectangleShape box1(sf::Vector2f(boxW, boxH));
        box1.setPosition(boxX, opt1Y - boxH / 2.0f);

        bool h1 = (hoveredChoice == SelectionConstants::CHOICE_IMAGE_LAB);
        if (h1) {
            box1.setFillColor(sf::Color(44, 65, 62, 240));
            box1.setOutlineColor(sf::Color(255, 225, 50, 255));
            box1.setOutlineThickness(2.5f);
        } else {
            box1.setFillColor(sf::Color(34, 49, 46, 230));
            box1.setOutlineColor(sf::Color(75, 100, 112, 230));
            box1.setOutlineThickness(2.0f);
        }
        window.draw(box1);

        sf::Text text1;
        text1.setFont(font);
        text1.setString("-> IMAGE LAB");
        text1.setCharacterSize(36);
        sf::FloatRect b1 = text1.getLocalBounds();
        text1.setOrigin(b1.left + b1.width / 2.0f, b1.top + b1.height / 2.0f);
        text1.setPosition(winW / 2.0f, opt1Y);

        if (h1) {
            text1.setFillColor(sf::Color(255, 235, 80));
        } else {
            text1.setFillColor(sf::Color(240, 245, 245));
        }
        window.draw(text1);

        // Card 2: -> VISUALIZATION
        outRect2 = sf::FloatRect(boxX, opt2Y - boxH / 2.0f, boxW, boxH);
        sf::RectangleShape box2(sf::Vector2f(boxW, boxH));
        box2.setPosition(boxX, opt2Y - boxH / 2.0f);

        bool h2 = (hoveredChoice == SelectionConstants::CHOICE_VISUALIZATION_STACK);
        if (h2) {
            box2.setFillColor(sf::Color(44, 65, 62, 240));
            box2.setOutlineColor(sf::Color(255, 225, 50, 255));
            box2.setOutlineThickness(2.5f);
        } else {
            box2.setFillColor(sf::Color(34, 49, 46, 230));
            box2.setOutlineColor(sf::Color(75, 100, 112, 230));
            box2.setOutlineThickness(2.0f);
        }
        window.draw(box2);

        sf::Text text2;
        text2.setFont(font);
        text2.setString("-> VISUALIZATION");
        text2.setCharacterSize(36);
        sf::FloatRect b2 = text2.getLocalBounds();
        text2.setOrigin(b2.left + b2.width / 2.0f, b2.top + b2.height / 2.0f);
        text2.setPosition(winW / 2.0f, opt2Y);

        if (h2) {
            text2.setFillColor(sf::Color(255, 235, 80));
        } else {
            text2.setFillColor(sf::Color(240, 245, 245));
        }
        window.draw(text2);
    }

}
