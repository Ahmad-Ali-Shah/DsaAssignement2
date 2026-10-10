#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "renderToolButton.h"
#include "../theme/drawBox.h"
#include "../theme/drawText.h"

namespace GraphicsToolbar {
    void renderToolPanel(sf::RenderWindow& win, const sf::Font& font, float barX, float barY, float barW, float barH, int mouseX, int mouseY, int undoCount, int redoCount) {
        GraphicsTheme::drawBox(win, barX, barY, barW, barH, sf::Color(18, 20, 26), sf::Color(35, 40, 50), 1.0f);
        GraphicsTheme::drawText(win, font, "IMAGELAB STUDIO", barX + 12.0f, barY + 12.0f, 16, sf::Color(255, 204, 0));

        float btnX = barX + 10.0f;
        float btnW = barW - 20.0f;
        float btnH = 26.0f;
        float curY = barY + 40.0f;

        // Instant Actions Group
        GraphicsTheme::drawText(win, font, "-- INSTANT TOOLS --", btnX, curY, 11, sf::Color(150, 160, 175));
        curY += 18.0f;

        renderToolButton(win, font, btnX, curY, btnW, btnH, "1. Load Image", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(35, 55, 80)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "2. Crop Rect", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(40, 45, 60)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "3. Rotate 90 deg", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(40, 45, 60)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "4. Flip Horizontal", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(40, 45, 60)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "5. Brightness (+20)", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(40, 45, 60)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "6. Grayscale", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(40, 45, 60)); curY += 36.0f;

        // History Management Group
        GraphicsTheme::drawText(win, font, "-- HISTORY CONTROLS --", btnX, curY, 11, sf::Color(150, 160, 175));
        curY += 18.0f;
        std::string undoLbl = "Undo (" + std::to_string(undoCount) + ")";
        renderToolButton(win, font, btnX, curY, btnW / 2.0f - 2.0f, btnH, undoLbl, mouseX >= btnX && mouseX <= btnX + btnW/2 - 2 && mouseY >= curY && mouseY <= curY + btnH, sf::Color(65, 45, 45));
        std::string redoLbl = "Redo (" + std::to_string(redoCount) + ")";
        renderToolButton(win, font, btnX + btnW / 2.0f + 2.0f, curY, btnW / 2.0f - 2.0f, btnH, redoLbl, mouseX >= btnX + btnW/2 + 2 && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(45, 55, 45));
        curY += 36.0f;

        // Queue Actions Group
        GraphicsTheme::drawText(win, font, "-- QUEUED JOBS --", btnX, curY, 11, sf::Color(150, 160, 175));
        curY += 18.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "Queue Resize (320x320)", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(38, 52, 68)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "Queue Blur (Radius 2)", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(38, 52, 68)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "Queue Fill (Stack DFS)", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(38, 52, 68)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "Queue Fill (Queue BFS)", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(38, 52, 68)); curY += 36.0f;

        // Pipeline Execution Controls
        GraphicsTheme::drawText(win, font, "-- PIPELINE CONTROLS --", btnX, curY, 11, sf::Color(150, 160, 175));
        curY += 18.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "Process Next Job", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(40, 75, 45)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "Process All Jobs", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(30, 85, 75)); curY += 30.0f;
        renderToolButton(win, font, btnX, curY, btnW, btnH, "Clear Pipeline", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(70, 35, 35)); curY += 36.0f;

        // Inspector Button
        renderToolButton(win, font, btnX, curY, btnW, btnH, "Toggle Inspector HUD", mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH, sf::Color(65, 50, 85));
    }
}
