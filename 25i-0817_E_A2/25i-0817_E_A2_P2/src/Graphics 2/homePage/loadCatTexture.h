#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace HomePage {

    bool loadCatTexture(sf::Texture& texture, const std::string& path) {
        if (!texture.loadFromFile(path)) {
            return false;
        }
        texture.setSmooth(false);
        return true;
    }

}
