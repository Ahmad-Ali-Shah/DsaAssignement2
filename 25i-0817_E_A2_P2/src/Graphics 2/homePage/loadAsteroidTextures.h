#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace HomePage {

    bool loadAsteroidTextures(sf::Texture textures[5], const std::string& baseDir) {
        for (int i = 0; i < 5; i++) {
            std::string path = baseDir + "/asteroid" + std::to_string(i + 1) + ".png";
            if (!textures[i].loadFromFile(path)) {
                return false;
            }
            textures[i].setSmooth(false);
        }
        return true;
    }

}
