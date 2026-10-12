#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace HomePage {

    bool loadHomeFonts(sf::Font& titleFont, sf::Font& sigFont, const std::string& fontDir) {
        bool titleLoaded = titleFont.loadFromFile(fontDir + "/KarmaticArcade.ttf");
        if (!titleLoaded) {
            titleLoaded = titleFont.loadFromFile(fontDir + "/Awesome.ttf");
        }
        if (!titleLoaded) {
            titleLoaded = titleFont.loadFromFile(fontDir + "/MetalSlug.ttf");
        }

        bool sigLoaded = sigFont.loadFromFile(fontDir + "/CType.ttf");
        if (!sigLoaded) {
            sigLoaded = sigFont.loadFromFile(fontDir + "/Cintarini.ttf");
        }
        if (!sigLoaded) {
            sigFont = titleFont;
        }

        return titleLoaded;
    }

}
