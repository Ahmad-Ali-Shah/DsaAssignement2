#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace InputPage {

    void renderLoadingScreen(sf::RenderWindow& window, const sf::Texture& catTex, const sf::Font& font, const sf::Font& titleFont, float catX, float catY, int catFrame, int loopsCompleted, const std::string& imagePath) {
        float winW = static_cast<float>(window.getSize().x);
        float centerY = 360.0f;

        // Dark modal shade surrounding the loading area
        float panelW = 760.0f;
        float panelH = 260.0f;
        float panelX = (winW - panelW) / 2.0f;
        float panelY = centerY - 130.0f;

        // Black shaded backdrop
        sf::RectangleShape shadeBox(sf::Vector2f(panelW, panelH));
        shadeBox.setPosition(panelX, panelY);
        shadeBox.setFillColor(sf::Color(0, 0, 0, 210));
        shadeBox.setOutlineColor(sf::Color(255, 225, 50, 200));
        shadeBox.setOutlineThickness(2.0f);
        window.draw(shadeBox);

        // Loading Header
        sf::Text loadTitle;
        loadTitle.setFont(titleFont);
        loadTitle.setString("LOADING IMAGE...");
        loadTitle.setCharacterSize(28);
        loadTitle.setStyle(sf::Text::Bold);
        sf::FloatRect ltb = loadTitle.getLocalBounds();
        loadTitle.setOrigin(ltb.left + ltb.width / 2.0f, ltb.top + ltb.height / 2.0f);
        loadTitle.setPosition(winW / 2.0f, panelY + 40.0f);
        loadTitle.setFillColor(sf::Color(255, 228, 50));
        window.draw(loadTitle);

        // Path indicator
        sf::Text pathText;
        pathText.setFont(font);
        pathText.setString("File: " + imagePath);
        pathText.setCharacterSize(22);
        sf::FloatRect ptb = pathText.getLocalBounds();
        pathText.setOrigin(ptb.left + ptb.width / 2.0f, ptb.top + ptb.height / 2.0f);
        pathText.setPosition(winW / 2.0f, panelY + 80.0f);
        pathText.setFillColor(sf::Color(180, 210, 240));
        window.draw(pathText);

        // Running track guideline
        float trackY = panelY + 180.0f;
        sf::RectangleShape track(sf::Vector2f(panelW - 60.0f, 3.0f));
        track.setPosition(panelX + 30.0f, trackY);
        track.setFillColor(sf::Color(60, 80, 100, 180));
        window.draw(track);

        // Animated running cat sprite (8 running frames)
        const int runRects[8][4] = {
            {513, 422, 27, 16},
            {547, 422, 27, 16},
            {579, 422, 27, 16},
            {610, 422, 27, 16},
            {642, 423, 27, 16},
            {674, 423, 27, 16},
            {706, 424, 27, 16},
            {738, 424, 26, 16}
        };

        int f = catFrame % 8;
        sf::Sprite cat(catTex);
        cat.setTextureRect(sf::IntRect(runRects[f][0], runRects[f][1], runRects[f][2], runRects[f][3]));
        cat.setOrigin(runRects[f][2] / 2.0f, static_cast<float>(runRects[f][3]));
        cat.setScale(3.5f, 3.5f);
        cat.setPosition(catX, catY);
        window.draw(cat);

        // Loop counter indicator
        sf::Text loopText;
        loopText.setFont(font);
        loopText.setString("Processing Pass: " + std::to_string(loopsCompleted + 1) + " / 3");
        loopText.setCharacterSize(20);
        sf::FloatRect lptb = loopText.getLocalBounds();
        loopText.setOrigin(lptb.left + lptb.width / 2.0f, lptb.top + lptb.height / 2.0f);
        loopText.setPosition(winW / 2.0f, panelY + panelH - 26.0f);
        loopText.setFillColor(sf::Color(150, 180, 200, 220));
        window.draw(loopText);
    }

}
