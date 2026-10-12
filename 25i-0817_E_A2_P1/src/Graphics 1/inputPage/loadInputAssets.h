#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace InputPage {

    bool loadInputAssets(sf::Texture& bgTex, sf::Texture& catTex, sf::Font& font, sf::Font& titleFont, const std::string& assetPath) {
        if (!bgTex.loadFromFile(assetPath + "/background2.jpeg")) {
            if (!bgTex.loadFromFile("25i-0817_E_A2_P1/background2.jpeg")) {
                bgTex.loadFromFile(assetPath + "/background.png");
            }
        }
        bgTex.setSmooth(true);

        if (!catTex.loadFromFile(assetPath + "/white_0.png")) {
            return false;
        }
        catTex.setSmooth(false);

        if (!titleFont.loadFromFile(assetPath + "/fonts/KarmaticArcade.ttf")) {
            titleFont.loadFromFile(assetPath + "/fonts/Pixeboy.ttf");
        }

        if (!font.loadFromFile(assetPath + "/fonts/Pixeboy.ttf")) {
            font = titleFont;
        }

        return true;
    }

}
