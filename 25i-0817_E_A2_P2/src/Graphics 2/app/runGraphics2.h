#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../window/initWindow2.h"
#include "handleToolExecution2.h"
#include "renderApp2.h"
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"

namespace GraphicsApp2 {
    int detectClickP2(float barX, float barY, float barW, int mouseX, int mouseY) {
        float btnX = barX + 10.0f;
        float btnW = barW - 20.0f;
        float btnH = 26.0f;
        float curY = barY + 40.0f;

        auto check = [&](int id) -> int {
            if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) return id;
            curY += 30.0f;
            return GraphicsTool2::NONE;
        };

        int id = check(GraphicsTool2::LOAD); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::CROP); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::ROTATE_90); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::FLIP_H); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::BRIGHTNESS_UP); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::GRAYSCALE); if (id != GraphicsTool2::NONE) return id;

        curY += 6.0f;
        id = check(GraphicsTool2::UNDO); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::REDO); if (id != GraphicsTool2::NONE) return id;

        curY += 6.0f;
        id = check(GraphicsTool2::TOGGLE_MODE); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::ENQUEUE_RESIZE); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::ENQUEUE_BLUR); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::ENQUEUE_BUCKET_STACK); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::ENQUEUE_BUCKET_QUEUE); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::ENQUEUE_SAVE); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::ENQUEUE_EXPORT); if (id != GraphicsTool2::NONE) return id;

        curY += 6.0f;
        id = check(GraphicsTool2::PROCESS_NEXT); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::PROCESS_ALL); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::CLEAR_PIPELINE); if (id != GraphicsTool2::NONE) return id;

        curY += 6.0f;
        id = check(GraphicsTool2::RUN_BENCHMARK); if (id != GraphicsTool2::NONE) return id;
        id = check(GraphicsTool2::TOGGLE_DUAL_FILL); if (id != GraphicsTool2::NONE) return id;

        return GraphicsTool2::NONE;
    }

    void runGraphics2(Pixel**& img, int& width, int& height, HistoryManager& history, ProcessingPipeline& pipeline) {
        sf::RenderWindow* win = GraphicsWindow2::initWindow2(1280, 800, "ImageLab Studio (Phase 2) - Priority Scheduler & Memory-Aware History");
        if (!win) return;

        sf::Font font;
        if (!font.loadFromFile("25i-0817_E_A2_P2/assets/fonts/Awesome.ttf")) {
            font.loadFromFile("25i-0817_E_A2_P2/assets/fonts/Pixeboy.ttf");
        }

        sf::Font sigFont;
        if (!sigFont.loadFromFile("25i-0817_E_A2_P2/assets/fonts/CType.ttf")) {
            sigFont = font;
        }

        sf::Texture canvasTex;
        if (img && width > 0 && height > 0) {
            sf::Uint8* pixels = new sf::Uint8[width * height * 4];
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int idx = (y * width + x) * 4;
                    pixels[idx] = static_cast<sf::Uint8>(img[y][x].r);
                    pixels[idx + 1] = static_cast<sf::Uint8>(img[y][x].g);
                    pixels[idx + 2] = static_cast<sf::Uint8>(img[y][x].b);
                    pixels[idx + 3] = 255;
                }
            }
            sf::Image sfImg;
            sfImg.create(width, height, pixels);
            delete[] pixels;
            canvasTex.loadFromImage(sfImg);
        }

        bool showDualFill = false;
        bool showBenchmark = false;
        std::string lastAction = "Phase 2 UI Initialized";
        int animFrame = 0;

        while (win->isOpen()) {
            sf::Event event;
            while (win->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    win->close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int toolId = detectClickP2(0.0f, 0.0f, 240.0f, event.mouseButton.x, event.mouseButton.y);
                        if (toolId != GraphicsTool2::NONE) {
                            handleToolExecution2(toolId, img, width, height, history, pipeline, showDualFill, showBenchmark, lastAction);
                            if (img && width > 0 && height > 0) {
                                sf::Uint8* pixels = new sf::Uint8[width * height * 4];
                                for (int y = 0; y < height; y++) {
                                    for (int x = 0; x < width; x++) {
                                        int idx = (y * width + x) * 4;
                                        pixels[idx] = static_cast<sf::Uint8>(img[y][x].r);
                                        pixels[idx + 1] = static_cast<sf::Uint8>(img[y][x].g);
                                        pixels[idx + 2] = static_cast<sf::Uint8>(img[y][x].b);
                                        pixels[idx + 3] = 255;
                                    }
                                }
                                sf::Image sfImg;
                                sfImg.create(width, height, pixels);
                                delete[] pixels;
                                canvasTex.loadFromImage(sfImg);
                            }
                        }
                    }
                }
            }

            animFrame++;
            sf::Vector2i mPos = sf::Mouse::getPosition(*win);
            renderApp2(*win, font, sigFont, canvasTex, mPos.x, mPos.y, history, pipeline, showDualFill, showBenchmark, lastAction, animFrame);
        }

        delete win;
    }
}
