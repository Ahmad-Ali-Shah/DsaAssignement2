#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "selectionConstants.h"
#include "loadSelectionAssets.h"
#include "updateShipSpeed.h"
#include "renderSelectionPage.h"

namespace SelectionPage {

    int runSelectionPage(sf::RenderWindow& window, const std::string& assetPath) {
        sf::Texture bgTex;
        sf::Texture shipTex;
        sf::Font mainFont;
        sf::Font titleFont;

        if (!loadSelectionAssets(bgTex, shipTex, mainFont, titleFont, assetPath)) {
            return SelectionConstants::CHOICE_IMAGE_LAB;
        }

        // Hide standard operating system mouse cursor in favor of custom spaceship cursor
        window.setMouseCursorVisible(false);

        sf::Clock clock;
        sf::Clock elapsedClock;

        sf::Vector2i initialPos = sf::Mouse::getPosition(window);
        float mouseX = static_cast<float>(initialPos.x);
        float mouseY = static_cast<float>(initialPos.y);
        float prevX = mouseX;
        float prevY = mouseY;
        bool isFast = false;
        int hoveredChoice = SelectionConstants::CHOICE_NONE;

        sf::FloatRect rect1;
        sf::FloatRect rect2;

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            if (dt > 0.05f) dt = 0.05f;

            float timeSeconds = elapsedClock.getElapsedTime().asSeconds();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.setMouseCursorVisible(true);
                    window.close();
                    return SelectionConstants::CHOICE_NONE;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        float cx = static_cast<float>(event.mouseButton.x);
                        float cy = static_cast<float>(event.mouseButton.y);
                        if (rect1.contains(cx, cy)) {
                            window.setMouseCursorVisible(true);
                            return SelectionConstants::CHOICE_IMAGE_LAB;
                        }
                        if (rect2.contains(cx, cy)) {
                            window.setMouseCursorVisible(true);
                            return SelectionConstants::CHOICE_VISUALIZATION_STACK;
                        }
                    }
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Return) {
                        window.setMouseCursorVisible(true);
                        return SelectionConstants::CHOICE_IMAGE_LAB;
                    }
                    if (event.key.code == sf::Keyboard::Num2) {
                        window.setMouseCursorVisible(true);
                        return SelectionConstants::CHOICE_VISUALIZATION_STACK;
                    }
                }
            }

            sf::Vector2i currPos = sf::Mouse::getPosition(window);
            mouseX = static_cast<float>(currPos.x);
            mouseY = static_cast<float>(currPos.y);

            updateShipSpeed(mouseX, mouseY, prevX, prevY, dt, SelectionConstants::SPEED_FAST_THRESHOLD, isFast);
            prevX = mouseX;
            prevY = mouseY;

            if (rect1.contains(mouseX, mouseY)) {
                hoveredChoice = SelectionConstants::CHOICE_IMAGE_LAB;
            } else if (rect2.contains(mouseX, mouseY)) {
                hoveredChoice = SelectionConstants::CHOICE_VISUALIZATION_STACK;
            } else {
                hoveredChoice = SelectionConstants::CHOICE_NONE;
            }

            renderSelectionPage(window, bgTex, shipTex, titleFont, mainFont, hoveredChoice, timeSeconds, mouseX, mouseY, isFast, rect1, rect2);
        }

        window.setMouseCursorVisible(true);
        return SelectionConstants::CHOICE_NONE;
    }

}
