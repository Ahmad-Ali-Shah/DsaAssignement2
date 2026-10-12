#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace SelectionPage {

    bool loadSelectionAssets(sf::Texture& bgTex, sf::Texture& shipTex, sf::Font& mainFont, sf::Font& titleFont, const std::string& assetPath) {
        if (!bgTex.loadFromFile(assetPath + "/background.png")) {
            return false;
        }
        bgTex.setSmooth(false);

        if (!shipTex.loadFromFile(assetPath + "/ship.png")) {
            return false;
        }
        shipTex.setSmooth(false);

        if (!titleFont.loadFromFile(assetPath + "/fonts/KarmaticArcade.ttf")) {
            titleFont.loadFromFile(assetPath + "/fonts/Pixeboy.ttf");
        }

        if (!mainFont.loadFromFile(assetPath + "/fonts/Pixeboy.ttf")) {
            mainFont = titleFont;
        }

        return true;
    }

}
