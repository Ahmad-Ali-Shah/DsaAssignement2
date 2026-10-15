#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <string>
#include <cmath>
#include "inputConstants.h"
#include "loadInputAssets.h"
#include "renderInputBackground.h"
#include "renderInputPrompt.h"
#include "renderLoadingScreen.h"
#include "validateAndLoadImage.h"
#include "../cursor/cursor.h"

namespace InputPage {

    bool runInputPage(sf::RenderWindow& window, const std::string& assetPath, Pixel**& img, int& width, int& height, std::string& outLoadedPath) {
        sf::Texture bgTex;
        sf::Texture catTex;
        sf::Texture shipTex;
        sf::Font font;
        sf::Font titleFont;

        if (!loadInputAssets(bgTex, catTex, shipTex, font, titleFont, assetPath)) {
            return false;
        }

        window.setMouseCursorVisible(false);

        float prevMouseX = 0.0f;
        float prevMouseY = 0.0f;
        bool isFastCursor = false;

        std::string enteredPath = "";
        std::string errorMsg = "";
        int currentState = InputConstants::stateTyping;

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

            sf::Vector2i mPos = sf::Mouse::getPosition(window);
            float mouseX = static_cast<float>(mPos.x);
            float mouseY = static_cast<float>(mPos.y);

            float dx = mouseX - prevMouseX;
            float dy = mouseY - prevMouseY;
            float dist = std::sqrt(dx * dx + dy * dy);
            isFastCursor = (dist / (dt > 0.0001f ? dt : 0.016f) >= 350.0f);
            prevMouseX = mouseX;
            prevMouseY = mouseY;

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

                if (currentState == InputConstants::stateTyping) {
                    if (event.type == sf::Event::KeyPressed) {
                        // Clipboard Paste (Ctrl+V)
                        if (event.key.control && event.key.code == sf::Keyboard::V) {
                            std::string clip = sf::Clipboard::getString().toAnsiString();
                            for (char c : clip) {
                                if (c >= 32 && c <= 126 && enteredPath.length() < 120) {
                                    enteredPath += c;
                                }
                            }
                            errorMsg = "";
                        }
                        // Clipboard Copy (Ctrl+C)
                        else if (event.key.control && event.key.code == sf::Keyboard::C) {
                            if (!enteredPath.empty()) {
                                sf::Clipboard::setString(enteredPath);
                            }
                        }
                        // Return / Submit
                        else if (event.key.code == sf::Keyboard::Return) {
                            if (enteredPath.empty()) {
                                errorMsg = "Path cannot be empty!";
                            } else {
                                if (validateAndLoadImage(enteredPath, img, width, height)) {
                                    outLoadedPath = enteredPath;
                                    currentState = InputConstants::stateLoading;
                                    catX = trackLeft;
                                    loopsCompleted = 0;
                                    errorMsg = "";
                                } else {
                                    errorMsg = "Failed to load image at: " + enteredPath;
                                }
                            }
                        }
                        // Escape
                        else if (event.key.code == sf::Keyboard::Escape) {
                            return false;
                        }
                    } else if (event.type == sf::Event::TextEntered) {
                        // Backspace
                        if (event.text.unicode == 8) {
                            if (!enteredPath.empty()) {
                                enteredPath.pop_back();
                                errorMsg = "";
                            }
                        }
                        // Ignore Ctrl characters (< 32 except return/backspace handled above)
                        else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                            if (enteredPath.length() < 120) {
                                enteredPath += static_cast<char>(event.text.unicode);
                                errorMsg = "";
                            }
                        }
                    }
                }
            }

            // Update loading cat animation
            if (currentState == InputConstants::stateLoading) {
                catTimer += dt;
                if (catTimer >= InputConstants::catFrameTime) {
                    catTimer -= InputConstants::catFrameTime;
                    catFrame = (catFrame + 1) % InputConstants::catRunFrames;
                }

                catX += InputConstants::catSpeed * dt;
                if (catX >= trackRight) {
                    catX = trackLeft;
                    loopsCompleted++;
                    if (loopsCompleted >= InputConstants::requiredCatLoops) {
                        return true;
                    }
                }
            }

            // Render loop
            window.clear(sf::Color::Black);
            renderInputBackground(window, bgTex);

            if (currentState == InputConstants::stateTyping) {
                renderInputPrompt(window, font, titleFont, enteredPath, cursorBlink, errorMsg);
            } else if (currentState == InputConstants::stateLoading) {
                renderLoadingScreen(window, catTex, font, titleFont, catX, catY, catFrame, loopsCompleted, outLoadedPath);
            }

            // Draw rocket custom cursor
            GraphicsCursor::renderCustomCursor(window, shipTex, mouseX, mouseY, isFastCursor);

            window.display();
        }

        return false;
    }

}
