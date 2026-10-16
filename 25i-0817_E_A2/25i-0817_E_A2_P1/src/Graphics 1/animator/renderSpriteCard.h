#pragma once
#include <SFML/Graphics.hpp>
#include "../theme/drawBox.h"

namespace GraphicsAnimator {
    void renderSpriteCard(sf::RenderWindow& win, const sf::Texture& tex, float x, float y, float w, float h, int frameX, int frameY, int tileW, int tileH) {

        if (tex.getSize().x == 0 || tex.getSize().y == 0) {

            GraphicsTheme::drawBox(win, x, y, w, h, sf::Color(45, 55, 75), sf::Color(0, 204, 255), 1.0f);

            return;

        }

        sf::Sprite sprite(tex);

        sprite.setTextureRect(sf::IntRect(frameX * tileW, frameY * tileH, tileW, tileH));

        sprite.setScale(w / static_cast<float>(tileW), h / static_cast<float>(tileH));

        sprite.setPosition(x, y);

        win.draw(sprite);
        
    }
}
