#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "inputConstants.h"
#include "loadInputAssets.h"
#include "renderInputBackground.h"
#include "renderInputPrompt.h"
#include "renderLoadingScreen.h"
#include "validateAndLoadImage.h"

namespace InputPage {

    bool runInputPage(sf::RenderWindow& window, const std::string& assetPath, Pixel**& img, int& width, int& height, std::string& outLoadedPath) {
        sf::Texture bgTex;
        sf::Texture catTex;
        sf::Font font;
        sf::Font titleFont;

        if (!loadInputAssets(bgTex, catTex, font, titleFont, assetPath)) {
            return false;
        }

        std::string enteredPath = "25i-0817_E_A2_P1/images/sample.ppm";
        std::string errorMsg = "";
        int currentState = InputConstants::STATE_TYPING;

        sf::Clock clock;
        sf::Clock blinkClock;
        bool cursorBlink = true;

        float winW = static_cast<float>(window.getSize().x);
        float trackLeft = (winW - 700.0f) / 2.0f;
        float trackRight = trackLeft + 700.0f;
        float catX = trackLeft;
        float catY = 360.0f + 50.0f;
        int catFrame = 0;
        float catTimer = 0.0f;
        int loopsCompleted = 0;

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            if (dt > 0.05f) dt = 0.05f;

            if (blinkClock.getElapsedTime().asSeconds() > 0.5f) {
                blinkClock.restart();
                cursorBlink = !cursorBlink;
            }

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return false;
                }

                if (currentState == InputConstants::STATE_TYPING) {
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode == 8) { // Backspace
                            if (!enteredPath.empty()) {
                                enteredPath.pop_back();
                                errorMsg = "";
                            }
                        } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                            if (enteredPath.length() < 90) {
                                enteredPath += static_cast<char>(event.text.unicode);
                                errorMsg = "";
                            }
                        }
                    } else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Return) {
                            if (enteredPath.empty()) {
                                errorMsg = "Path cannot be empty!";
                            } else {
                                // Validate if file can be opened
                                if (validateAndLoadImage(enteredPath, img, width, height)) {
                                    outLoadedPath = enteredPath;
                                    currentState = InputConstants::STATE_LOADING;
                                    catX = trackLeft;
                                    loopsCompleted = 0;
                                    errorMsg = "";
                                } else {
                                    errorMsg = "Failed to load image at: " + enteredPath;
                                }
                            }
                        } else if (event.key.code == sf::Keyboard::Escape) {
                            return false;
                        }
                    }
                }
            }

            // Update loading cat animation
            if (currentState == InputConstants::STATE_LOADING) {
                catTimer += dt;
                if (catTimer >= InputConstants::CAT_FRAME_TIME) {
                    catTimer -= InputConstants::CAT_FRAME_TIME;
                    catFrame = (catFrame + 1) % InputConstants::CAT_RUN_FRAMES;
                }

                catX += InputConstants::CAT_SPEED * dt;
                if (catX >= trackRight) {
                    catX = trackLeft;
                    loopsCompleted++;
                    if (loopsCompleted >= 3) {
                        // Finished 3 passes!
                        return true;
                    }
                }
            }

            // Render loop
            window.clear(sf::Color::Black);
            renderInputBackground(window, bgTex);

            if (currentState == InputConstants::STATE_TYPING) {
                renderInputPrompt(window, font, titleFont, enteredPath, cursorBlink, errorMsg);
            } else if (currentState == InputConstants::STATE_LOADING) {
                renderLoadingScreen(window, catTex, font, titleFont, catX, catY, catFrame, loopsCompleted, outLoadedPath);
            }

            window.display();
        }

        return false;
    }

}
