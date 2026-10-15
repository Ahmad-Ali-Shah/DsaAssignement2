#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "renderSpriteCard.h"
#include "../theme/drawBox.h"
#include "../theme/drawText.h"






namespace GraphicsAnimator {

    void renderDataStructureAnimation(sf::RenderWindow& win, const sf::Font& font, const sf::Texture& spriteTex, float animX, float animY, float animW, float animH, int stackSize, int queueSize, const std::string& lastAction) {

        GraphicsTheme::drawBox(win, animX, animY, animW, animH, sf::Color(20, 24, 32), sf::Color(55, 65, 80), 1.0f);

        GraphicsTheme::drawText(win, font, "LIVE DATA STRUCTURE ANIMATOR", animX + 10.0f, animY + 8.0f, 13, sf::Color(0, 255, 200));

       
        float blockW = 28.0f;

        float blockH = 16.0f;

        float stackBaseY = animY + animH - 18.0f;

        float stackBaseX = animX + 25.0f;


        GraphicsTheme::drawText(win, font, "STACK", stackBaseX, animY + 30.0f, 11, sf::Color(255, 180, 0));

        int visibleStack = stackSize > 5 ? 5 : stackSize;

        for (int i = 0; i < visibleStack; i++) {

            float curY = stackBaseY - (i * (blockH + 4.0f));

            renderSpriteCard(win, spriteTex, stackBaseX, curY, blockW, blockH, (i % 2), 0, 128, 64);

        }

        // Draw animated queue elements

        float qBaseX = animX + 90.0f;

        float qBaseY = animY + animH - 30.0f;

        GraphicsTheme::drawText(win, font, "CIRCULAR QUEUE", qBaseX, animY + 30.0f, 11, sf::Color(0, 204, 255));

        int visibleQueue = queueSize > 5 ? 5 : queueSize;

        for (int i = 0; i < visibleQueue; i++) {

            float curX = qBaseX + (i * (blockW + 4.0f));

            renderSpriteCard(win, spriteTex, curX, qBaseY, blockW, blockH, (i % 2), 1, 128, 64);
            
        }

        // Action banner
        if (!lastAction.empty()) {

            GraphicsTheme::drawText(win, font, "Action: " + lastAction, animX + 10.0f, animY + animH - 14.0f, 11, sf::Color(255, 255, 120));
            
        }
    }
}
