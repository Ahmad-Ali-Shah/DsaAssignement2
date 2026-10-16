#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "visConstants.h"

namespace VisPage {

    bool loadVisAssets(VisConstants::VisTextures& tex, sf::Font& font, sf::Font& titleFont, const std::string& assetPath) {
        if (!tex.bg.loadFromFile(assetPath + "/Bg3.jpg")) {
            tex.bg.loadFromFile(assetPath + "/background.png");
        }
        tex.bg.setSmooth(true);

        tex.banner.loadFromFile(assetPath + "/banner.png");
        tex.banner.setSmooth(false);

        tex.blocks.loadFromFile(assetPath + "/Blocks.png");
        tex.blocks.setSmooth(false);

        tex.tools.loadFromFile(assetPath + "/tools.png");
        tex.tools.setSmooth(false);

        tex.rotations.loadFromFile(assetPath + "/Rotations.png");
        tex.rotations.setSmooth(false);

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
