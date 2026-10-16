#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace InputPage {

    void renderInputPrompt(sf::RenderWindow& window, const sf::Font& font, const sf::Font& titleFont, const std::string& enteredText, bool cursorBlink, const std::string& errorMsg) {
        float winW = static_cast<float>(window.getSize().x);
        float centerY = 360.0f;

        // Header Title
        sf::Text title;
        title.setFont(titleFont);
        title.setString("ENTER IMAGE PATH");
        title.setCharacterSize(34);
        title.setStyle(sf::Text::Bold);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
        title.setPosition(winW / 2.0f, centerY - 100.0f);

        // Shadow & glowing text
        title.setFillColor(sf::Color(0, 0, 0, 220));
        title.move(3.0f, 3.0f);
        window.draw(title);
        title.move(-3.0f, -3.0f);
        title.setFillColor(sf::Color(255, 228, 50));
        window.draw(title);

        // Subtitle prompt label
        sf::Text label;
        label.setFont(font);
        label.setString("Enter correct path of image :");
        label.setCharacterSize(26);
        sf::FloatRect lb = label.getLocalBounds();
        label.setOrigin(lb.left + lb.width / 2.0f, lb.top + lb.height / 2.0f);
        label.setPosition(winW / 2.0f, centerY - 40.0f);
        label.setFillColor(sf::Color(230, 240, 250));
        window.draw(label);

        // Input Box
        float boxW = 760.0f;
        float boxH = 56.0f;
        float boxX = (winW - boxW) / 2.0f;
        float boxY = centerY;

        sf::RectangleShape box(sf::Vector2f(boxW, boxH));
        box.setPosition(boxX, boxY);
        box.setFillColor(sf::Color(20, 28, 38, 220));
        box.setOutlineColor(sf::Color(100, 160, 220, 240));
        box.setOutlineThickness(2.5f);
        window.draw(box);

        // Entered path string with cursor
        std::string displayText = enteredText;
        if (cursorBlink) {
            displayText += "_";
        }

        sf::Text inputVal;
        inputVal.setFont(font);
        inputVal.setString(displayText);
        inputVal.setCharacterSize(28);
        inputVal.setFillColor(sf::Color(255, 255, 255));
        inputVal.setPosition(boxX + 16.0f, boxY + 12.0f);
        window.draw(inputVal);

        // Instruction hint
        sf::Text hint;
        hint.setFont(font);
        hint.setString("Press ENTER to Load  |  Formats: PNG, JPG, BMP, PPM");
        hint.setCharacterSize(22);
        sf::FloatRect hb = hint.getLocalBounds();
        hint.setOrigin(hb.left + hb.width / 2.0f, hb.top + hb.height / 2.0f);
        hint.setPosition(winW / 2.0f, centerY + 80.0f);
        hint.setFillColor(sf::Color(160, 185, 210, 200));
        window.draw(hint);

        // Error message if path is invalid
        if (!errorMsg.empty()) {
            sf::Text err;
            err.setFont(font);
            err.setString(errorMsg);
            err.setCharacterSize(24);
            sf::FloatRect eb = err.getLocalBounds();
            err.setOrigin(eb.left + eb.width / 2.0f, eb.top + eb.height / 2.0f);
            err.setPosition(winW / 2.0f, centerY + 120.0f);
            err.setFillColor(sf::Color(255, 80, 80));
            window.draw(err);
        }
    }

}
