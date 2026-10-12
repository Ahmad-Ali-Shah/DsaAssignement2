#pragma once
#include <SFML/Graphics.hpp>
#include "renderSelectionBackground.h"
#include "renderSelectionTitle.h"
#include "renderSelectionOptions.h"
#include "renderShipCursor.h"

namespace SelectionPage {

    void renderSelectionPage(sf::RenderWindow& window, const sf::Texture& bgTex, const sf::Texture& shipTex, const sf::Font& titleFont, const sf::Font& mainFont, int hoveredChoice, float timeSeconds, float mouseX, float mouseY, bool isFast, sf::FloatRect& outRect1, sf::FloatRect& outRect2) {
        window.clear(sf::Color::Black);

        renderSelectionBackground(window, bgTex);
        renderSelectionTitle(window, titleFont, timeSeconds);
        renderSelectionOptions(window, mainFont, hoveredChoice, outRect1, outRect2);
        renderShipCursor(window, shipTex, mouseX, mouseY, isFast);

        window.display();
    }

}
