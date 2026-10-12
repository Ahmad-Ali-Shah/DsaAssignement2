#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "visConstants.h"
#include "loadVisAssets.h"
#include "renderDataWindow.h"
#include "renderVisControls.h"
#include "updateVisAnimation.h"
#include "../editorPage/editorConstants.h"
#include "../editorPage/loadEditorAssets.h"
#include "../editorPage/renderEditorBanner.h"
#include "../editorPage/renderMiddleCanvas.h"
#include "../editorPage/renderLeftToolbar.h"
#include "../editorPage/renderParameterModal.h"
#include "../editorPage/executeEditorAction.h"
#include "../canvas/createTextureFromPixels.h"
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"

namespace VisPage {

    void runVisPage(sf::RenderWindow& window, const std::string& assetPath, Pixel**& img, int& width, int& height, HistoryManager& history, ProcessingPipeline& pipeline) {
        (void)pipeline;
        VisConstants::VisTextures vTex;
        EditorPage::EditorTextures eTex;
        sf::Font font;
        sf::Font titleFont;

        if (!loadVisAssets(vTex, font, titleFont, assetPath)) return;
        EditorPage::loadEditorAssets(eTex, font, titleFont, assetPath);

        sf::Texture canvasTex;
        if (img && width > 0 && height > 0) {
            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
        }

        std::string currentOp = "Current Image";
        std::string statusMsg = "Visualization Active - Inspect Array Cells or Animate Operations";

        // Stack array representation items
        std::string mainStack[VisConstants::MAX_STACK_ITEMS];
        int mainTop = 4;
        mainStack[0] = "Root Base";
        mainStack[1] = "PPM Matrix";
        mainStack[2] = "Crop 50%";
        mainStack[3] = "Rotate 90";
        mainStack[4] = "Grayscale";

        // Auxiliary stack ("Other Stack") for pop-and-repush animation
        std::string auxStack[VisConstants::MAX_STACK_ITEMS];
        int auxTop = -1;

        // Circular Queue array representation items
        std::string queueArr[VisConstants::MAX_QUEUE_ITEMS];
        int queueFront = 0;
        int queueRear = 2;
        int queueCount = 3;
        queueArr[0] = "Task #1: Blur";
        queueArr[1] = "Task #2: Gray";
        queueArr[2] = "Task #3: Bucket";

        VisConstants::SubWindow stackWin;
        stackWin.visible = true;
        stackWin.minimized = false;
        stackWin.type = 1;

        VisConstants::SubWindow queueWin;
        queueWin.visible = false;
        queueWin.minimized = false;
        queueWin.type = 2;

        VisConstants::VisAnimController anim;
        anim.animType = 0;
        anim.timer = 0.0f;
        anim.currentStep = 0;
        anim.stepDuration = 0.65f;

        EditorPage::LeftButtonRects leftRects;
        VisConstants::VisButtonRects visRects;
        EditorPage::ModalInputs modal;
        modal.active = false;
        sf::FloatRect modalOkRect, modalCancelRect;
        sf::FloatRect stackCloseRect, stackMinRect;
        sf::FloatRect queueCloseRect, queueMinRect;

        sf::Clock clock;

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            if (dt > 0.05f) dt = 0.05f;

            sf::Vector2i mPos = sf::Mouse::getPosition(window);
            float mouseX = static_cast<float>(mPos.x);
            float mouseY = static_cast<float>(mPos.y);

            // Step active animations
            updateVisAnimation(anim, dt, img, width, height, canvasTex, mainStack, mainTop, auxStack, auxTop, queueArr, queueFront, queueRear, queueCount, currentOp, statusMsg);

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }

                // Modal typing
                if (modal.active) {
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode == 8) {
                            if (modal.activeField == 1 && !modal.val1.empty()) modal.val1.pop_back();
                            else if (modal.activeField == 2 && !modal.val2.empty()) modal.val2.pop_back();
                        } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                            if (modal.activeField == 1 && modal.val1.length() < 12) modal.val1 += static_cast<char>(event.text.unicode);
                            else if (modal.activeField == 2 && modal.val2.length() < 12) modal.val2 += static_cast<char>(event.text.unicode);
                        }
                    } else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Return) {
                            if (EditorPage::executeEditorAction(modal.opType, img, width, height, history, modal.val1, modal.val2, currentOp)) {
                                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                                if (mainTop < 7) {
                                    mainTop++;
                                    mainStack[mainTop] = currentOp;
                                }
                            }
                            modal.active = false;
                        } else if (event.key.code == sf::Keyboard::Escape) {
                            modal.active = false;
                        }
                    } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        if (modalOkRect.contains(mouseX, mouseY)) {
                            if (EditorPage::executeEditorAction(modal.opType, img, width, height, history, modal.val1, modal.val2, currentOp)) {
                                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                                if (mainTop < 7) {
                                    mainTop++;
                                    mainStack[mainTop] = currentOp;
                                }
                            }
                            modal.active = false;
                        } else if (modalCancelRect.contains(mouseX, mouseY)) {
                            modal.active = false;
                        }
                    }
                    continue;
                }

                // Mouse clicks
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    // Subwindow close and minimize controls
                    if (stackWin.visible) {
                        if (stackCloseRect.contains(mouseX, mouseY)) {
                            stackWin.visible = false;
                        } else if (stackMinRect.contains(mouseX, mouseY)) {
                            stackWin.minimized = !stackWin.minimized;
                        }
                    }
                    if (queueWin.visible) {
                        if (queueCloseRect.contains(mouseX, mouseY)) {
                            queueWin.visible = false;
                        } else if (queueMinRect.contains(mouseX, mouseY)) {
                            queueWin.minimized = !queueWin.minimized;
                        }
                    }

                    // Right visualization buttons
                    if (visRects.showStackBtn.contains(mouseX, mouseY)) {
                        stackWin.visible = true;
                        stackWin.minimized = false;
                        queueWin.visible = false;
                    } else if (visRects.showQueueBtn.contains(mouseX, mouseY)) {
                        queueWin.visible = true;
                        queueWin.minimized = false;
                        stackWin.visible = false;
                    } else if (visRects.animDataBtn.contains(mouseX, mouseY)) {
                        stackWin.visible = true;
                        stackWin.minimized = false;
                        queueWin.visible = false;
                        anim.animType = VisConstants::ANIM_STACK_POP_PUSH;
                        anim.currentStep = 0;
                        anim.timer = 0.0f;
                    } else if (visRects.animImageBtn.contains(mouseX, mouseY)) {
                        anim.animType = VisConstants::ANIM_IMAGE_STEPS;
                        anim.currentStep = 0;
                        anim.timer = 0.0f;
                    }

                    // Left toolbar operations: apply transformation and push to stack
                    else if (leftRects.rot90Btn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_ROT_90, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Rot 90"; }
                        }
                    } else if (leftRects.rot180Btn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_ROT_180, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Rot 180"; }
                        }
                    } else if (leftRects.rot270Btn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_ROT_270, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Rot 270"; }
                        }
                    } else if (leftRects.rot360Btn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_ROT_360, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Rot 360"; }
                        }
                    } else if (leftRects.flipHBtn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_FLIP_H, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Flip H"; }
                        }
                    } else if (leftRects.flipVBtn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_FLIP_V, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Flip V"; }
                        }
                    } else if (leftRects.grayBtn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_GRAYSCALE, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Grayscale"; }
                        }
                    } else if (leftRects.blurBtn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_BLUR, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Box Blur"; }
                        }
                    } else if (leftRects.bucketBtn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_BUCKET_FILL, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Bucket"; }
                        }
                    } else if (leftRects.resizeBtn.contains(mouseX, mouseY)) {
                        if (EditorPage::executeEditorAction(EditorConstants::OP_RESIZE, img, width, height, history, "", "", currentOp)) {
                            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            if (mainTop < 7) { mainTop++; mainStack[mainTop] = "Resize"; }
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

            // Draw full visualization screen
            window.clear(sf::Color::Black);
            sf::Sprite bg(vTex.bg);
            bg.setScale(static_cast<float>(window.getSize().x) / vTex.bg.getSize().x, static_cast<float>(window.getSize().y) / vTex.bg.getSize().y);
            window.draw(bg);

            EditorPage::renderMiddleCanvas(window, canvasTex, width, height, font);
            EditorPage::renderLeftToolbar(window, eTex, font, mouseX, mouseY, leftRects);
            renderVisControls(window, font, mouseX, mouseY, visRects);
            EditorPage::renderEditorBanner(window, vTex.banner, font, currentOp);

            if (stackWin.visible) {
                renderDataWindow(window, font, titleFont, stackWin, mainStack, mainTop, auxStack, auxTop, queueArr, queueFront, queueRear, queueCount, statusMsg, stackCloseRect, stackMinRect);
            }
            if (queueWin.visible) {
                renderDataWindow(window, font, titleFont, queueWin, mainStack, mainTop, auxStack, auxTop, queueArr, queueFront, queueRear, queueCount, statusMsg, queueCloseRect, queueMinRect);
            }
            if (modal.active) {
                EditorPage::renderParameterModal(window, font, titleFont, modal, modalOkRect, modalCancelRect);
            }

            window.display();
        }
    }

}
