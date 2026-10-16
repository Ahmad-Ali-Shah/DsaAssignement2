#pragma once
#include <SFML/Graphics.hpp>

namespace HomePage {

    void renderAsteroidCorner(sf::RenderTarget& target, const sf::Texture textures[5], int frameIdx, float x, float y, float scale) {
        if (frameIdx < 0 || frameIdx >= 5) {
            frameIdx = 0;
        }

        sf::Sprite asteroid;
        asteroid.setTexture(textures[frameIdx]);
        sf::Vector2u size = textures[frameIdx].getSize();
        asteroid.setOrigin(size.x / 2.0f, size.y / 2.0f);
        asteroid.setScale(scale, scale);
        asteroid.setPosition(x, y);

        target.draw(asteroid);
    }

}
