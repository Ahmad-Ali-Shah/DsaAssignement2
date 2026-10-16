#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace EditorPage {

    void renderMiddleCanvas(sf::RenderWindow& window, const sf::Texture& canvasTex, int origW, int origH, const sf::Font& font) {
        float winW = static_cast<float>(window.getSize().x);
        float boxW = 580.0f;
        float boxH = 460.0f;
        float boxX = (winW - boxW) / 2.0f;
        float boxY = 180.0f;

        // Outer Canvas Box
        sf::RectangleShape box(sf::Vector2f(boxW, boxH));
        box.setPosition(boxX, boxY);
        box.setFillColor(sf::Color(15, 20, 28, 230));
        box.setOutlineColor(sf::Color(80, 140, 200, 240));
        box.setOutlineThickness(3.0f);
        window.draw(box);

        // Header tag for canvas with high-contrast badge background
        std::string headerStr = "CANVAS VIEW (" + std::to_string(origW) + "x" + std::to_string(origH) + ")";
        
        sf::Text header;
        header.setFont(font);
        header.setString(headerStr);
        header.setCharacterSize(15);
        sf::FloatRect hb = header.getLocalBounds();

        float badgeW = hb.width + 24.0f;
        float badgeH = 26.0f;
        float badgeX = boxX + 14.0f;
        float badgeY = boxY - 30.0f;

        // Dark arcade badge plate
        sf::RectangleShape badge(sf::Vector2f(badgeW, badgeH));
        badge.setPosition(badgeX, badgeY);
        badge.setFillColor(sf::Color(12, 20, 32, 240));
        badge.setOutlineColor(sf::Color(75, 140, 220, 240));
        badge.setOutlineThickness(1.5f);
        window.draw(badge);

        // Text shadow for extra contrast
        sf::Text headerShadow;
        headerShadow.setFont(font);
        headerShadow.setString(headerStr);
        headerShadow.setCharacterSize(15);
        headerShadow.setFillColor(sf::Color(0, 0, 0, 230));
        headerShadow.setPosition(badgeX + 13.0f, badgeY + 4.5f);
        window.draw(headerShadow);

        // Vibrant yellow arcade text
        header.setFillColor(sf::Color(255, 228, 65));
        header.setPosition(badgeX + 12.0f, badgeY + 3.5f);
        window.draw(header);

        // Draw image sprite centered inside the box
        if (canvasTex.getSize().x > 0 && canvasTex.getSize().y > 0) {
            sf::Sprite imgSprite(canvasTex);
            float imgW = static_cast<float>(canvasTex.getSize().x);
            float imgH = static_cast<float>(canvasTex.getSize().y);

            float scale = 1.0f;
            float maxW = boxW - 20.0f;
            float maxH = boxH - 20.0f;
            if (imgW > maxW || imgH > maxH) {
                float sW = maxW / imgW;
                float sH = maxH / imgH;
                scale = (sW < sH) ? sW : sH;
            }

            imgSprite.setScale(scale, scale);
            float posX = boxX + (boxW - imgW * scale) / 2.0f;
            float posY = boxY + (boxH - imgH * scale) / 2.0f;
            imgSprite.setPosition(posX, posY);
            window.draw(imgSprite);
        }
    }

}
