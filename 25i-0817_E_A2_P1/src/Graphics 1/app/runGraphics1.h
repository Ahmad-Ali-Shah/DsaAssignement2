#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../window/initWindow.h"
#include "../theme/loadFont.h"
#include "../canvas/createTextureFromPixels.h"
#include "../toolbar/detectToolClick.h"
#include "../animator/loadSpriteSheet.h"
#include "handleToolExecution.h"
#include "renderApp.h"
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"

namespace GraphicsApp {
    void runGraphics1(Pixel**& img, int& width, int& height, HistoryManager& history, ProcessingPipeline& pipeline) {
        sf::RenderWindow* win = GraphicsWindow::initWindow(1280, 800, "ImageLab Studio (Phase 1) - Data Structures & Core Editor");
        if (!win) return;

        sf::Font font;
        GraphicsTheme::loadFont(font, "25i-0817_E_A2_P1/assets/fonts/Pixeboy.ttf");

        sf::Texture spriteTex;
        GraphicsAnimator::loadSpriteSheet(spriteTex, "25i-0817_E_A2_P1/assets/stack_queue_spritesheet.jpg");

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
                        if (toolId != GraphicsTool::NONE) {
                            handleToolExecution(toolId, img, width, height, history, pipeline, showInspector, lastAction);
                            if (img && width > 0 && height > 0) {
                                GraphicsCanvas::createTextureFromPixels(canvasTex, img, width, height);
                            }
                        }
                    }
                }
            }

            sf::Vector2i mPos = sf::Mouse::getPosition(*win);
            renderApp(*win, font, canvasTex, spriteTex, mPos.x, mPos.y, history, pipeline, showInspector, lastAction);
        }

        delete win;
    }
}
