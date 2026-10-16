#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../theme/drawBadge.h"

namespace GraphicsCoalescing {
    void renderCoalescingBadge(sf::RenderWindow& win, const sf::Font& font, float x, float y, const std::string& topOpName) {
        if (topOpName.find("Brightness") != std::string::npos) {
            GraphicsTheme2::drawBadge(win, font, x, y, "[COALESCED RECORD] " + topOpName, sf::Color(40, 100, 60), sf::Color(255, 255, 255));
        } else {
            GraphicsTheme2::drawBadge(win, font, x, y, "[ACTIVE RECORD] " + topOpName, sf::Color(45, 60, 80), sf::Color(220, 220, 220));
        }
    }
}
