#pragma once
#include <SFML/Graphics.hpp>

namespace GraphicsCursor {

    void renderCustomCursor(sf::RenderWindow& window, const sf::Texture& shipTex, float mouseX, float mouseY, bool isFast) {
        sf::Sprite ship(shipTex);

        if (isFast) {
            ship.setTextureRect(sf::IntRect(3, 0, 42, 44));
            ship.setOrigin(21.0f, 4.0f);
        } else {
            ship.setTextureRect(sf::IntRect(51, 0, 42, 42));
            ship.setOrigin(21.0f, 4.0f);
        }

        ship.setScale(1.35f, 1.35f);
        ship.setPosition(mouseX, mouseY);
        window.draw(ship);
    }

}
