#pragma once
#include <SFML/Graphics.hpp>
#include "homeConstants.h"

namespace HomePage {

    void renderCatSprite(sf::RenderTarget& target, const sf::Texture& catTex, int stage, int frameIdx, float catX, float catY, float scale) {
        sf::IntRect sittingFrames[7] = {
            sf::IntRect(99, 422, 25, 18),
            sf::IntRect(131, 422, 23, 18),
            sf::IntRect(163, 422, 25, 18),
            sf::IntRect(195, 422, 25, 18),
            sf::IntRect(227, 422, 25, 18),
            sf::IntRect(259, 422, 25, 18),
            sf::IntRect(291, 422, 25, 18)
        };

        sf::IntRect standingFrames[2] = {
            sf::IntRect(323, 423, 25, 17),
            sf::IntRect(355, 424, 26, 16)
        };

        sf::IntRect walkingFrames[4] = {
            sf::IntRect(391, 422, 21, 18),
            sf::IntRect(423, 421, 21, 19),
            sf::IntRect(455, 422, 21, 18),
            sf::IntRect(487, 421, 21, 19)
        };

        sf::IntRect runningFrames[8] = {
            sf::IntRect(513, 422, 27, 16),
            sf::IntRect(545, 423, 27, 17),
            sf::IntRect(578, 424, 26, 16),
            sf::IntRect(609, 422, 27, 18),
            sf::IntRect(641, 421, 27, 15),
            sf::IntRect(673, 422, 27, 18),
            sf::IntRect(705, 423, 27, 17),
            sf::IntRect(738, 424, 26, 16)
        };

        sf::IntRect rect(99, 422, 25, 18);
        if (stage == HomeConstants::stageSitting) {
            if (frameIdx >= 0 && frameIdx < 7) rect = sittingFrames[frameIdx];
        } else if (stage == HomeConstants::stageStanding) {
            if (frameIdx >= 0 && frameIdx < 2) rect = standingFrames[frameIdx];
        } else if (stage == HomeConstants::stageWalking) {
            if (frameIdx >= 0 && frameIdx < 4) rect = walkingFrames[frameIdx];
        } else if (stage == HomeConstants::stageRunning) {
            if (frameIdx >= 0 && frameIdx < 8) rect = runningFrames[frameIdx];
        }

        sf::Sprite sprite;
        sprite.setTexture(catTex);
        sprite.setTextureRect(rect);
        sprite.setScale(scale, scale);
        sprite.setPosition(catX, catY);

        target.draw(sprite);
    }

}
