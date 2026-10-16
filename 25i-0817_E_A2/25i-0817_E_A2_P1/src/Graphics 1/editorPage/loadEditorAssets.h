#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace EditorPage {

    struct EditorTextures {
        sf::Texture bg;
        sf::Texture banner;
        sf::Texture imageLoad;
        sf::Texture crop;
        sf::Texture rotations;
        sf::Texture tools;
        sf::Texture arrow;
        sf::Texture adjustment;
    };

    bool loadEditorAssets(EditorTextures& tex, sf::Font& font, sf::Font& titleFont, const std::string& assetPath) {
        tex.bg.loadFromFile(assetPath + "/background2.jpeg");
        tex.bg.setSmooth(true);

        tex.banner.loadFromFile(assetPath + "/banner.png");
        tex.banner.setSmooth(false);

        tex.imageLoad.loadFromFile(assetPath + "/imageLoad.png");
        tex.imageLoad.setSmooth(false);

        tex.crop.loadFromFile(assetPath + "/crop.png");
        tex.crop.setSmooth(false);

        tex.rotations.loadFromFile(assetPath + "/Rotations.png");
        tex.rotations.setSmooth(false);

        tex.tools.loadFromFile(assetPath + "/tools.png");
        tex.tools.setSmooth(false);

        tex.arrow.loadFromFile(assetPath + "/arrow.png");
        tex.arrow.setSmooth(false);

        tex.adjustment.loadFromFile(assetPath + "/Adjustment.png");
        tex.adjustment.setSmooth(false);

        if (!titleFont.loadFromFile(assetPath + "/fonts/KarmaticArcade.ttf")) {
            titleFont.loadFromFile(assetPath + "/fonts/Pixeboy.ttf");
        }

        if (!font.loadFromFile(assetPath + "/fonts/Pixeboy.ttf")) {
            font = titleFont;
        }

        return true;
    }

}
