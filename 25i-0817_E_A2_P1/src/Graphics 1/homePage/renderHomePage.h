#pragma once
#include <SFML/Graphics.hpp>
#include "renderAsteroidCorner.h"
#include "renderHomeTitle.h"
#include "renderCatSprite.h"

namespace HomePage {

    void renderHomePage(sf::RenderWindow& window, const sf::Texture astTex[5], int astFrame,
                        const sf::Texture& catTex, int catStage, int catFrame, float catX, float catY,
                        const sf::Font& titleFont, const sf::Font& sigFont, bool reachedEnd) {
        window.clear(sf::Color::Black);

        float winW = static_cast<float>(window.getSize().x);
        float winH = static_cast<float>(window.getSize().y);

        renderAsteroidCorner(window, astTex, astFrame, winW - 100.0f, 90.0f, 3.5f);

        renderHomeTitle(window, titleFont, sigFont, winW, winH);

        renderCatSprite(window, catTex, catStage, catFrame, catX, catY, 4.0f);

        if (reachedEnd) {
            sf::Text prompt;
            prompt.setFont(titleFont);
            prompt.setString("[ Click or Press ENTER to Continue ]");
            prompt.setCharacterSize(16);
            prompt.setFillColor(sf::Color(160, 220, 255));
            sf::FloatRect pb = prompt.getLocalBounds();
            prompt.setPosition((winW - pb.width) / 2.0f, winH * 0.82f);
            window.draw(prompt);
        }

        window.display();
    }

}
