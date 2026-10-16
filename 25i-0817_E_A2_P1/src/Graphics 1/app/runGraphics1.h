#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../window/initWindow.h"
#include "../theme/loadFont.h"
#include "../canvas/createTextureFromPixels.h"
#include "../toolbar/detectToolClick.h"
#include "../animator/loadSpriteSheet.h"
#include "../homePage/runHomePage.h"
#include "../selectionPage/runSelectionPage.h"
#include "../inputPage/runInputPage.h"
#include "../editorPage/runEditorPage.h"
#include "../visPage/runVisPage.h"
#include "handleToolExecution.h"
#include "renderApp.h"
#include "resolveAssetPath.h"
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"

namespace GraphicsApp {
    void runGraphics1(Pixel**& img, int& width, int& height, HistoryManager& history, ProcessingPipeline& pipeline) {
        sf::RenderWindow* win = GraphicsWindow::initWindow(1280, 800, "ImageLab Studio (Phase 1)");
        if (!win) return;

        std::string assetDir = GraphicsAssetHelper::resolveAssetPath("25i-0817_E_A2_P1/assets", ".");

        bool proceed = HomePage::runHomePage(*win, assetDir);
        if (!proceed || !win->isOpen()) {
            delete win;
            return;
        }

        while (win->isOpen()) {
            int choice = SelectionPage::runSelectionPage(*win, assetDir);
            if (choice == SelectionConstants::choiceNone || !win->isOpen()) {
                break;
            }

            std::string loadedImagePath = "";
            if (choice == SelectionConstants::choiceImageLab) {
                bool inputOk = InputPage::runInputPage(*win, assetDir, img, width, height, loadedImagePath);
                if (!inputOk || !win->isOpen()) {
                    continue; // Back to selection page
                }

                EditorPage::runEditorPage(*win, assetDir, img, width, height, history, pipeline, loadedImagePath);
                continue; // Back to selection page when editor finishes / back clicked
            } else if (choice == SelectionConstants::choiceVisualizationStack) {
                bool inputOk = InputPage::runInputPage(*win, assetDir, img, width, height, loadedImagePath);
                if (!inputOk || !win->isOpen()) {
                    continue; // Back to selection page
                }

                VisPage::runVisPage(*win, assetDir, img, width, height, history, pipeline);
                continue; // Back to selection page when vis finishes / back clicked
            }
        }

        delete win;
        return;

        sf::Font font;
        std::string fontPath1 = GraphicsAssetHelper::resolveAssetPath("25i-0817_E_A2_P1/assets/fonts/Awesome.ttf", ".");
        std::string fontPath2 = GraphicsAssetHelper::resolveAssetPath("25i-0817_E_A2_P1/assets/fonts/Pixeboy.ttf", ".");
        if (!GraphicsTheme::loadFont(font, fontPath1)) {
            GraphicsTheme::loadFont(font, fontPath2);
        }

        sf::Font sigFont;
        if (!GraphicsTheme::loadFont(sigFont, "25i-0817_E_A2_P1/assets/fonts/CType.ttf")) {
            sigFont = font;
        }

        sf::Texture spriteTex;
        if (!GraphicsAnimator::loadSpriteSheet(spriteTex, "25i-0817_E_A2_P1/assets/cube_spritesheet_transparent.png")) {
            GraphicsAnimator::loadSpriteSheet(spriteTex, "25i-0817_E_A2_P1/assets/stack_queue_spritesheet.png");
        }

        sf::Texture canvasTex;
        if (img && width > 0 && height > 0) {
            GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
        }

        bool showInspector = false;
        std::string lastAction = "UI Ready";

        while (win->isOpen()) {
            sf::Event event;
            while (win->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    win->close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int toolId = GraphicsToolbar::detectToolClick(0.0f, 0.0f, 240.0f, event.mouseButton.x, event.mouseButton.y);
                        if (toolId != GraphicsTool::none) {
                            handleToolExecution(toolId, img, width, height, history, pipeline, showInspector, lastAction);
                            if (img && width > 0 && height > 0) {
                                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            }
                        }
                    }
                }
            }

            sf::Vector2i mPos = sf::Mouse::getPosition(*win);
            renderApp(*win, font, sigFont, canvasTex, spriteTex, mPos.x, mPos.y, history, pipeline, showInspector, lastAction);
        }

        delete win;
    }
}
