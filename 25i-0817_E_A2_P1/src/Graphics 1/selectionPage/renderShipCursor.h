#pragma once
#include <SFML/Graphics.hpp>
#include "selectionConstants.h"

namespace SelectionPage {

    void renderShipCursor(sf::RenderWindow& window, const sf::Texture& shipTex, float mouseX, float mouseY, bool isFast) {
        sf::Sprite ship(shipTex);

        if (isFast) {
            ship.setTextureRect(sf::IntRect(
                SelectionConstants::shipFrameFastX,
                SelectionConstants::shipFrameFastY,
                SelectionConstants::shipFrameFastW,
                SelectionConstants::shipFrameFastH
            ));
            ship.setOrigin(
                SelectionConstants::shipFrameFastW / 2.0f,
                SelectionConstants::shipFrameFastH / 2.0f
            );
        } else {
            ship.setTextureRect(sf::IntRect(
                SelectionConstants::shipFrameSlowX,
                SelectionConstants::shipFrameSlowY,
                SelectionConstants::shipFrameSlowW,
                SelectionConstants::shipFrameSlowH
            ));
            ship.setOrigin(
                SelectionConstants::shipFrameSlowW / 2.0f,
                SelectionConstants::shipFrameSlowH / 2.0f
            );
        }

        // Clean crisp pixel art scaling (no tilt, direct cursor replacement)
        ship.setScale(1.6f, 1.6f);
        ship.setPosition(mouseX, mouseY);
        window.draw(ship);
    }

}
