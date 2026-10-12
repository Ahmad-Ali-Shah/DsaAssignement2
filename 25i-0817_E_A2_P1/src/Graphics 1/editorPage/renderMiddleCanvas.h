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

        // Header tag for canvas
        sf::Text header;
        header.setFont(font);
        header.setString("CANVAS VIEW (" + std::to_string(origW) + "x" + std::to_string(origH) + ")");
        header.setCharacterSize(18);
        header.setFillColor(sf::Color(200, 220, 240));
        header.setPosition(boxX + 16.0f, boxY - 24.0f);
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
