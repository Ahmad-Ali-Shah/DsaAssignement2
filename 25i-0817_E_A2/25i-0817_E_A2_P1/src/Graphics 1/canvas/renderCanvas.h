#pragma once
#include <SFML/Graphics.hpp>
#include "../theme/drawBox.h"

namespace GraphicsCanvas {
    void renderCanvas(sf::RenderWindow& win, const sf::Texture& tex, float viewX, float viewY, float viewW, float viewH) {

        GraphicsTheme::drawBox(win, viewX, viewY, viewW, viewH, sf::Color(25, 28, 36), sf::Color(45, 52, 65), 1.0f);

        if (tex.getSize().x == 0 || tex.getSize().y == 0) 
        return;


        sf::Sprite sprite(tex);

        float scaleX = (viewW - 20.0f) / tex.getSize().x;

        float scaleY = (viewH - 20.0f) / tex.getSize().y;

        float scale = scaleX < scaleY ? scaleX : scaleY;

        if (scale > 1.0f) scale = 1.0f;

        sprite.setScale(scale, scale);

        float drawW = tex.getSize().x * scale;

        float drawH = tex.getSize().y * scale;

        float posX = viewX + (viewW - drawW) / 2.0f;

        float posY = viewY + (viewH - drawH) / 2.0f;

        sprite.setPosition(posX, posY);
        
        win.draw(sprite);
    }
}
