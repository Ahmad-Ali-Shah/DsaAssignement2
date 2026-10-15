#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../window/initWindow2.h"
#include "../homePage/runHomePage.h"
#include "../selectionPage/runSelectionPage.h"
#include "../inputPage/runInputPage.h"
#include "../editorPage/runEditorPage.h"
#include "../visPage/runVisPage.h"
#include "handleToolExecution2.h"
#include "renderApp2.h"
#include "resolveAssetPath.h"
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"

namespace GraphicsApp2 {
    struct ClickChecker {
        float btnX;
        float btnW;
        float btnH;
        float& curY;
        int mouseX;
        int mouseY;

        int operator()(int id) const {
            if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) return id;
            curY += 30.0f;
            return GraphicsTool2::none;
        }
    };

    int detectClickP2(float barX, float barY, float barW, int mouseX, int mouseY) {
        float btnX = barX + 10.0f;
        float btnW = barW - 20.0f;
        float btnH = 26.0f;
        float curY = barY + 40.0f;

        ClickChecker check{btnX, btnW, btnH, curY, mouseX, mouseY};

        int id = check(GraphicsTool2::load); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::crop); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::rotate90); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::flipH); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::brightnessUp); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::grayscale); if (id != GraphicsTool2::none) return id;

        curY += 6.0f;
        id = check(GraphicsTool2::undo); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::redo); if (id != GraphicsTool2::none) return id;

        curY += 6.0f;
        id = check(GraphicsTool2::toggleMode); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::enqueueResize); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::enqueueBlur); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::enqueueBucketStack); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::enqueueBucketQueue); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::enqueueSave); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::enqueueExport); if (id != GraphicsTool2::none) return id;

        curY += 6.0f;
        id = check(GraphicsTool2::processNext); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::processAll); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::clearPipeline); if (id != GraphicsTool2::none) return id;

        curY += 6.0f;
        id = check(GraphicsTool2::runBenchmark); if (id != GraphicsTool2::none) return id;
        id = check(GraphicsTool2::toggleDualFill); if (id != GraphicsTool2::none) return id;

        return GraphicsTool2::none;
    }

    void runGraphics2(Pixel**& img, int& width, int& height, HistoryManager& history, ProcessingPipeline& pipeline) {
        sf::RenderWindow* win = GraphicsWindow2::initWindow2(1280, 800, "ImageLab Studio (Phase 2) - Priority Scheduler & Memory-Aware History");
        if (!win) return;

        std::string assetDir = GraphicsAssetHelper::resolveAssetPath("25i-0817_E_A2_P2/All Req Assests", ".");

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
        std::string fontPath1 = GraphicsAssetHelper::resolveAssetPath("25i-0817_E_A2_P2/assets/fonts/Awesome.ttf", ".");
        std::string fontPath2 = GraphicsAssetHelper::resolveAssetPath("25i-0817_E_A2_P2/assets/fonts/Pixeboy.ttf", ".");
        if (!font.loadFromFile(fontPath1)) {
            font.loadFromFile(fontPath2);
        }

        sf::Font sigFont;
        std::string fontPath3 = GraphicsAssetHelper::resolveAssetPath("25i-0817_E_A2_P2/assets/fonts/CType.ttf", ".");
        if (!sigFont.loadFromFile(fontPath3)) {
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
                        if (toolId != GraphicsTool2::none) {
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
