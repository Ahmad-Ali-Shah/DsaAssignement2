#pragma once
#include <SFML/Graphics.hpp>

namespace InputPage {

    void renderInputBackground(sf::RenderWindow& window, const sf::Texture& bgTex) {
        sf::Sprite bg(bgTex);
        float winW = static_cast<float>(window.getSize().x);
        float winH = static_cast<float>(window.getSize().y);
        float texW = static_cast<float>(bgTex.getSize().x);
        float texH = static_cast<float>(bgTex.getSize().y);

        if (texW > 0.0f && texH > 0.0f) {
            bg.setScale(winW / texW, winH / texH);
        }
        window.draw(bg);

        // Dark retro aesthetic overlay for contrast
        sf::RectangleShape shade(sf::Vector2f(winW, winH));
        shade.setFillColor(sf::Color(10, 15, 20, 110));
        window.draw(shade);
    }

}
