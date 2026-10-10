#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../scheduler/renderPriorityQueueBar.h"
#include "../memoryGauge/renderMemoryBudgetMeter.h"
#include "../coalescingView/renderCoalescingBadge.h"
#include "../dualFill/renderDualFillComparison.h"
#include "../benchmarkView/renderSchedulerComparisonTable.h"
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"

namespace GraphicsApp2 {
    void renderApp2(sf::RenderWindow& win, const sf::Font& font, const sf::Texture& canvasTex, int mouseX, int mouseY, HistoryManager& history, ProcessingPipeline& pipeline, bool showDualFill, bool showBenchmark, const std::string& lastAction, int animFrame) {
        win.clear(sf::Color(12, 14, 18));

        // 1. Sidebar Toolbar
        float barX = 0.0f;
        float barY = 0.0f;
        float barW = 240.0f;
        float barH = 800.0f;

        sf::RectangleShape side(sf::Vector2f(barW, barH));
        side.setPosition(barX, barY);
        side.setFillColor(sf::Color(18, 20, 26));
        side.setOutlineColor(sf::Color(35, 40, 50));
        side.setOutlineThickness(1.0f);
        win.draw(side);

        sf::Text title;
        title.setFont(font);
        title.setString("IMAGELAB PHASE 2 STUDIO");
        title.setCharacterSize(15);
        title.setFillColor(sf::Color(255, 204, 0));
        title.setPosition(barX + 10.0f, barY + 12.0f);
        win.draw(title);

        float btnX = barX + 10.0f;
        float btnW = barW - 20.0f;
        float btnH = 26.0f;
        float curY = barY + 40.0f;

        auto drawBtn = [&](const std::string& lbl, sf::Color bg) {
            bool hov = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH);
            sf::RectangleShape b(sf::Vector2f(btnW, btnH));
            b.setPosition(btnX, curY);
            b.setFillColor(hov ? sf::Color(bg.r + 25, bg.g + 25, bg.b + 25) : bg);
            b.setOutlineColor(hov ? sf::Color(255, 204, 0) : sf::Color(80, 90, 110));
            b.setOutlineThickness(1.0f);
            win.draw(b);

            sf::Text t;
            t.setFont(font);
            t.setString(lbl);
            t.setCharacterSize(12);
            t.setFillColor(sf::Color(240, 240, 240));
            t.setPosition(btnX + 8.0f, curY + 5.0f);
            win.draw(t);
            curY += 30.0f;
        };

        drawBtn("1. Load Image", sf::Color(35, 55, 80));
        drawBtn("2. Crop Region (50%)", sf::Color(40, 45, 60));
        drawBtn("3. Rotate 90 deg", sf::Color(40, 45, 60));
        drawBtn("4. Flip Horizontal", sf::Color(40, 45, 60));
        drawBtn("5. Brightness +20", sf::Color(40, 45, 60));
        drawBtn("6. Grayscale", sf::Color(40, 45, 60));

        curY += 6.0f;
        drawBtn("Undo (" + std::to_string(history.getUndoSize()) + ")", sf::Color(65, 45, 45));
        drawBtn("Redo (" + std::to_string(history.getRedoSize()) + ")", sf::Color(45, 55, 45));

        curY += 6.0f;
        std::string modeLbl = (pipeline.getMode() == SchedulerMode::FIFO) ? "Switch -> Priority Mode" : "Switch -> FIFO Mode";
        drawBtn(modeLbl, sf::Color(80, 60, 20));
        drawBtn("Enqueue Resize [P3]", sf::Color(38, 52, 68));
        drawBtn("Enqueue Blur [P2]", sf::Color(38, 52, 68));
        drawBtn("Enqueue Fill (Stack) [P2]", sf::Color(38, 52, 68));
        drawBtn("Enqueue Fill (Queue) [P2]", sf::Color(38, 52, 68));
        drawBtn("Enqueue Save [P4 Barrier]", sf::Color(60, 35, 70));
        drawBtn("Enqueue Export [P4 Barrier]", sf::Color(60, 35, 70));

        curY += 6.0f;
        drawBtn("Dispatch Next Job", sf::Color(40, 75, 45));
        drawBtn("Dispatch All Jobs", sf::Color(30, 85, 75));
        drawBtn("Clear Pipeline", sf::Color(70, 35, 35));

        curY += 6.0f;
        drawBtn("Toggle Benchmark Table", sf::Color(45, 70, 85));
        drawBtn("Toggle Dual Fill View", sf::Color(35, 65, 75));

        // 2. Main Canvas Viewport
        sf::RectangleShape canvasBox(sf::Vector2f(750.0f, 540.0f));
        canvasBox.setPosition(245.0f, 10.0f);
        canvasBox.setFillColor(sf::Color(25, 28, 36));
        canvasBox.setOutlineColor(sf::Color(45, 52, 65));
        canvasBox.setOutlineThickness(1.0f);
        win.draw(canvasBox);

        if (canvasTex.getSize().x > 0 && canvasTex.getSize().y > 0) {
            sf::Sprite sprite(canvasTex);
            float scaleX = 730.0f / canvasTex.getSize().x;
            float scaleY = 520.0f / canvasTex.getSize().y;
            float scale = scaleX < scaleY ? scaleX : scaleY;
            if (scale > 1.0f) scale = 1.0f;
            sprite.setScale(scale, scale);
            float drawW = canvasTex.getSize().x * scale;
            float drawH = canvasTex.getSize().y * scale;
            sprite.setPosition(245.0f + (750.0f - drawW) / 2.0f, 10.0f + (540.0f - drawH) / 2.0f);
            win.draw(sprite);
        }

        // 3. Top-Right Memory Gauge and Coalescing Badges
        GraphicsMemory::renderMemoryBudgetMeter(win, font, 1000.0f, 10.0f, 270.0f, 80.0f, history);
        GraphicsCoalescing::renderCoalescingBadge(win, font, 1005.0f, 100.0f, history.getUndoTopName());

        // Status banner
        sf::Text statText;
        statText.setFont(font);
        statText.setString("Action: " + lastAction);
        statText.setCharacterSize(12);
        statText.setFillColor(sf::Color(255, 255, 120));
        statText.setPosition(1005.0f, 130.0f);
        win.draw(statText);

        // 4. Bottom Priority Scheduler Bar
        GraphicsScheduler::renderPriorityQueueBar(win, font, 245.0f, 560.0f, 1025.0f, 230.0f, pipeline);

        // 5. Overlays
        if (showBenchmark) {
            GraphicsBenchmark::renderSchedulerComparisonTable(win, font, 350.0f, 80.0f, 580.0f, 240.0f);
        }
        if (showDualFill) {
            GraphicsDualFill::renderDualFillComparison(win, font, 280.0f, 100.0f, 720.0f, 380.0f, animFrame);
        }

        win.display();
    }
}
