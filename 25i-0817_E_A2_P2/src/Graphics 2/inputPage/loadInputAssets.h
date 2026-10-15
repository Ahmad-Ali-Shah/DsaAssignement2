#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace InputPage {

    bool loadInputAssets(sf::Texture& bgTex, sf::Texture& catTex, sf::Texture& shipTex, sf::Font& font, sf::Font& titleFont, const std::string& assetPath) {
        if (!bgTex.loadFromFile(assetPath + "/background2.jpeg")) {
            bgTex.loadFromFile(assetPath + "/background.png");
        }
        bgTex.setSmooth(true);

        if (!catTex.loadFromFile(assetPath + "/white0.png")) {
            return false;
        }
        catTex.setSmooth(false);

        if (!shipTex.loadFromFile(assetPath + "/ship.png")) {
            // Non-fatal if ship missing
        }
        shipTex.setSmooth(false);

        if (!titleFont.loadFromFile(assetPath + "/fonts/KarmaticArcade.ttf")) {
            titleFont.loadFromFile(assetPath + "/fonts/Pixeboy.ttf");
        }

        if (!font.loadFromFile(assetPath + "/fonts/Pixeboy.ttf")) {
            font = titleFont;
        }

        return true;
    }

}
