#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "editorConstants.h"
#include "loadEditorAssets.h"
#include "renderEditorBanner.h"
#include "renderMiddleCanvas.h"
#include "renderLeftToolbar.h"
#include "renderRightPanel.h"
#include "renderParameterModal.h"
#include "executeEditorAction.h"
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"
#include "../../read/mainLogic/reader.h"
#include "../../read/mainLogic/deleter.h"
#include "../canvas/createTextureFromPixels.h"
#include "../cursor/cursor.h"
#include <cmath>

namespace EditorPage {

    void runEditorPage(sf::RenderWindow& window, const std::string& assetPath, Pixel**& img, int& width, int& height, HistoryManager& history, ProcessingPipeline& pipeline, const std::string& initialImagePath) {
        (void)pipeline;
        EditorTextures tex;
        sf::Font font;
        sf::Font titleFont;

        if (!loadEditorAssets(tex, font, titleFont, assetPath)) {
            return;
        }

        sf::Texture shipTex;
        shipTex.loadFromFile(assetPath + "/ship.png");
        window.setMouseCursorVisible(false);

        float prevMouseX = 0.0f;
        float prevMouseY = 0.0f;
        bool isFastCursor = false;

        sf::Texture canvasTex;
        if (img && width > 0 && height > 0) {
            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
        }

        std::string currentOp = "Current Image";
        std::string savePath = "25i-0817_E_A2_P1/images/saved.png";
        bool isTypingSave = false;

        ModalInputs modal;
        modal.active = false;

        LeftButtonRects leftRects;
        RightButtonRects rightRects;
        sf::FloatRect modalOkRect, modalCancelRect;

        sf::Clock clock;

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

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }

                // Modal typing
                if (modal.active) {
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode == 8) { // Backspace
                            if (modal.activeField == 1 && !modal.val1.empty()) modal.val1.pop_back();
                            else if (modal.activeField == 2 && !modal.val2.empty()) modal.val2.pop_back();
                        } else if (event.text.unicode == 9) { // Tab
                            modal.activeField = (modal.activeField == 1) ? 2 : 1;
                        } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                            if (modal.activeField == 1 && modal.val1.length() < 12) modal.val1 += static_cast<char>(event.text.unicode);
                            else if (modal.activeField == 2 && modal.val2.length() < 12) modal.val2 += static_cast<char>(event.text.unicode);
                        }
                    } else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Return) {
                            if (executeEditorAction(modal.opType, img, width, height, history, modal.val1, modal.val2, currentOp)) {
                                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            }
                            modal.active = false;
                        } else if (event.key.code == sf::Keyboard::Escape) {
                            modal.active = false;
                        }
                    } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        if (modalOkRect.contains(mouseX, mouseY)) {
                            if (executeEditorAction(modal.opType, img, width, height, history, modal.val1, modal.val2, currentOp)) {
                                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            }
                            modal.active = false;
                        } else if (modalCancelRect.contains(mouseX, mouseY)) {
                            modal.active = false;
                        }
                    }
                    continue;
                }

                // Save path typing
                if (isTypingSave) {
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode == 8) {
                            if (!savePath.empty()) savePath.pop_back();
                        } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                            if (savePath.length() < 70) savePath += static_cast<char>(event.text.unicode);
                        }
                    } else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Return) {
                            isTypingSave = false;
                            executeEditorAction(EditorConstants::OP_SAVE, img, width, height, history, savePath, "", currentOp);
                        } else if (event.key.code == sf::Keyboard::Escape) {
                            isTypingSave = false;
                        }
                    }
                }

                // Mouse click on tools and buttons
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (rightRects.savePathBox.contains(mouseX, mouseY)) {
                        isTypingSave = true;
                    } else {
                        isTypingSave = false;
                    }

                    if (rightRects.saveBtn.contains(mouseX, mouseY)) {
                        executeEditorAction(EditorConstants::OP_SAVE, img, width, height, history, savePath, "", currentOp);
                    } else if (rightRects.reloadBtn.contains(mouseX, mouseY)) {
                        int rw = 0, rh = 0;
                        Pixel** reloaded = ReadPath::ReadImage(initialImagePath, rw, rh);
                        if (reloaded && rw > 0 && rh > 0) {
                            history.recordGridOperation("Reload", HistoryOpType::RESIZE, img, width, height);
                            ReadPath::freeImage(img, height);
                            img = reloaded;
                            width = rw;
                            height = rh;
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            currentOp = "Reloaded Original";
                        }
                    } else if (rightRects.undoBtn.contains(mouseX, mouseY)) {
                        if (history.canUndo()) {
                            history.undo(img, width, height);
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            currentOp = "Undo";
                        }
                    } else if (rightRects.redoBtn.contains(mouseX, mouseY)) {
                        if (history.canRedo()) {
                            history.redo(img, width, height);
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            currentOp = "Redo";
                        }
                    }
                    // Left toolbar clicks
                    else if (leftRects.rot90Btn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_ROT_90, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.rot180Btn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_ROT_180, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.rot270Btn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_ROT_270, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.rot360Btn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_ROT_360, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.flipHBtn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_FLIP_H, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.flipVBtn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_FLIP_V, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.grayBtn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_GRAYSCALE, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.blurBtn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_BLUR, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.bucketBtn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_BUCKET_FILL, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.resizeBtn.contains(mouseX, mouseY)) {
                        if (executeEditorAction(EditorConstants::OP_RESIZE, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                        }
                    } else if (leftRects.brightBtn.contains(mouseX, mouseY)) {
                        modal.active = true;
                        modal.title = "ADJUST BRIGHTNESS";
                        modal.label1 = "Enter Delta (-255 to 255)";
                        modal.label2 = "";
                        modal.val1 = "40";
                        modal.val2 = "";
                        modal.activeField = 1;
                        modal.opType = EditorConstants::OP_BRIGHTNESS;
                    } else if (leftRects.cropBtn.contains(mouseX, mouseY)) {
                        modal.active = true;
                        modal.title = "CROP IMAGE DIMENSIONS";
                        modal.label1 = "Target Width";
                        modal.label2 = "Target Height";
                        modal.val1 = std::to_string(width / 2);
                        modal.val2 = std::to_string(height / 2);
                        modal.activeField = 1;
                        modal.opType = EditorConstants::OP_CROP;
                    }
                }
            }

            // Draw full screen
            window.clear(sf::Color::Black);
            sf::Sprite bg(tex.bg);
            bg.setScale(static_cast<float>(window.getSize().x) / tex.bg.getSize().x, static_cast<float>(window.getSize().y) / tex.bg.getSize().y);
            window.draw(bg);

            renderMiddleCanvas(window, canvasTex, width, height, font);
            renderLeftToolbar(window, tex, font, mouseX, mouseY, leftRects);
            renderRightPanel(window, font, mouseX, mouseY, savePath, isTypingSave, rightRects);
            renderEditorBanner(window, tex.banner, font, currentOp);

            if (modal.active) {
                renderParameterModal(window, font, titleFont, modal, modalOkRect, modalCancelRect);
            }

            GraphicsCursor::renderCustomCursor(window, shipTex, mouseX, mouseY, isFastCursor);

            window.display();
        }

        window.setMouseCursorVisible(true);
    }

}
