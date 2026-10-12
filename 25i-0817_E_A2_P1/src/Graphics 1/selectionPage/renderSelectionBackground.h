#pragma once
#include <SFML/Graphics.hpp>

namespace SelectionPage {

    void renderSelectionBackground(sf::RenderWindow& window, const sf::Texture& bgTex) {
        sf::Sprite bgSprite(bgTex);
        float winW = static_cast<float>(window.getSize().x);
        float winH = static_cast<float>(window.getSize().y);
        float texW = static_cast<float>(bgTex.getSize().x);
        float texH = static_cast<float>(bgTex.getSize().y);

        if (texW > 0.0f && texH > 0.0f) {
            bgSprite.setScale(winW / texW, winH / texH);
        }
        window.draw(bgSprite);

        // Soft dark vignette overlay to make crisp yellow arcade typography pop
        sf::RectangleShape overlay(sf::Vector2f(winW, winH));
        overlay.setFillColor(sf::Color(0, 0, 0, 85));
        window.draw(overlay);
    }

}
