#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "homeConstants.h"
#include "loadAsteroidTextures.h"
#include "loadCatTexture.h"
#include "loadHomeFonts.h"
#include "updateCatState.h"
#include "renderHomePage.h"

namespace HomePage {

    bool runHomePage(sf::RenderWindow& window, const std::string& assetPath) {
        sf::Texture astTex[5];
        if (!loadAsteroidTextures(astTex, assetPath + "/asteroids")) {
            return true;
        }

        sf::Texture catTex;
        if (!loadCatTexture(catTex, assetPath + "/white0.png")) {
            return true;
        }

        sf::Font titleFont;
        sf::Font sigFont;
        loadHomeFonts(titleFont, sigFont, assetPath + "/fonts");

        float winW = static_cast<float>(window.getSize().x);
        float winH = static_cast<float>(window.getSize().y);

        float catX = 80.0f;
        float catY = winH * 0.44f - 110.0f;
        int catStage = HomeConstants::stageSitting;
        int catFrame = 0;
        float catTimer = 0.0f;
        int sitLoops = 0;
        bool reachedEnd = false;

        int astFrame = 0;
        float astTimer = 0.0f;
        float astFrameDuration = 0.12f;

        sf::Clock clock;

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            if (dt > 0.05f) dt = 0.05f;

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return false;
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                        return true;
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        return true;
                    }
                }
            }

            astTimer += dt;
            if (astTimer >= astFrameDuration) {
                astTimer -= astFrameDuration;
                astFrame = (astFrame + 1) % 5;
            }

            if (!reachedEnd) {
                updateCatState(catStage, catFrame, catTimer, catX, dt, winW, sitLoops, reachedEnd);
            }

            renderHomePage(window, astTex, astFrame, catTex, catStage, catFrame, catX, catY, titleFont, sigFont, reachedEnd);
        }

        return false;
    }

}
