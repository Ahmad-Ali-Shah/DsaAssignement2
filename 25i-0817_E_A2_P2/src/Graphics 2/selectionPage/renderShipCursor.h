#pragma once
#include <SFML/Graphics.hpp>
#include "selectionConstants.h"

namespace SelectionPage {

    void renderShipCursor(sf::RenderWindow& window, const sf::Texture& shipTex, float mouseX, float mouseY, bool isFast) {
        sf::Sprite ship(shipTex);

        if (isFast) {
            ship.setTextureRect(sf::IntRect(
                SelectionConstants::SHIP_FRAME_FAST_X,
                SelectionConstants::SHIP_FRAME_FAST_Y,
                SelectionConstants::SHIP_FRAME_FAST_W,
                SelectionConstants::SHIP_FRAME_FAST_H
            ));
            ship.setOrigin(
                SelectionConstants::SHIP_FRAME_FAST_W / 2.0f,
                SelectionConstants::SHIP_FRAME_FAST_H / 2.0f
            );
        } else {
            ship.setTextureRect(sf::IntRect(
                SelectionConstants::SHIP_FRAME_SLOW_X,
                SelectionConstants::SHIP_FRAME_SLOW_Y,
                SelectionConstants::SHIP_FRAME_SLOW_W,
                SelectionConstants::SHIP_FRAME_SLOW_H
            ));
            ship.setOrigin(
                SelectionConstants::SHIP_FRAME_SLOW_W / 2.0f,
                SelectionConstants::SHIP_FRAME_SLOW_H / 2.0f
            );
        }

        // Clean crisp pixel art scaling (no tilt, direct cursor replacement)
        ship.setScale(1.6f, 1.6f);
        ship.setPosition(mouseX, mouseY);
        window.draw(ship);
    }

}
