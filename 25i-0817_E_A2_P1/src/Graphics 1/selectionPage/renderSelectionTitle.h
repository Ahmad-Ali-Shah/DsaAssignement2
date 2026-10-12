#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

namespace SelectionPage {

    void renderSelectionTitle(sf::RenderWindow& window, const sf::Font& font, float timeSeconds) {
        float winW = static_cast<float>(window.getSize().x);

        sf::Text titleText;
        titleText.setFont(font);
        titleText.setString("Select your choice");
        titleText.setCharacterSize(36);
        titleText.setStyle(sf::Text::Bold);

        sf::FloatRect bounds = titleText.getLocalBounds();
        titleText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

        float posX = winW / 2.0f;
        float posY = 150.0f;

        // Subtle pulsing glow for arcade effect
        float pulse = (std::sin(timeSeconds * 4.0f) + 1.0f) * 0.5f;
        sf::Uint8 pulseAlpha = static_cast<sf::Uint8>(180 + pulse * 75);

        // Drop shadow for crisp readability against starfield / planet background
        titleText.setPosition(posX + 4.0f, posY + 4.0f);
        titleText.setFillColor(sf::Color(0, 0, 0, 220));
        window.draw(titleText);

        titleText.setPosition(posX + 2.0f, posY + 2.0f);
        titleText.setFillColor(sf::Color(140, 90, 0, 200));
        window.draw(titleText);

        // Main glowing yellow bold text
        titleText.setPosition(posX, posY);
        titleText.setFillColor(sf::Color(255, 228, 50, pulseAlpha));
        window.draw(titleText);
    }

}
