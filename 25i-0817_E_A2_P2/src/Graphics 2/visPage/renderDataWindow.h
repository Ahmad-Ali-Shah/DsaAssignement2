#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "visConstants.h"

namespace VisPage {

    void renderDataWindow(sf::RenderWindow& window,
                          const sf::Font& font,
                          const sf::Font& titleFont,
                          VisConstants::SubWindow& subWin,
                          const std::string mainStack[],
                          int mainTop,
                          const std::string auxStack[],
                          int auxTop,
                          const std::string queueArr[],
                          int queueFront,
                          int queueRear,
                          int queueCount,
                          const std::string& statusMsg,
                          sf::FloatRect& closeBtnRect,
                          sf::FloatRect& minBtnRect) {
        if (!subWin.visible) return;

        float winW = static_cast<float>(window.getSize().x);
        subWin.w = 760.0f;
        subWin.h = subWin.minimized ? 42.0f : 490.0f;
        subWin.x = (winW - subWin.w) / 2.0f;
        subWin.y = subWin.minimized ? 660.0f : 120.0f;

        // Dim background overlay when expanded
        if (!subWin.minimized) {
            sf::RectangleShape dim(sf::Vector2f(winW, static_cast<float>(window.getSize().y)));
            dim.setFillColor(sf::Color(0, 0, 0, 165));
            window.draw(dim);
        }

        // Subwindow main box: Deep blue background with cyber arcade glow
        sf::RectangleShape box(sf::Vector2f(subWin.w, subWin.h));
        box.setPosition(subWin.x, subWin.y);
        box.setFillColor(sf::Color(10, 26, 56, 248));
        box.setOutlineColor(sf::Color(55, 140, 240, 255));
        box.setOutlineThickness(3.0f);
        window.draw(box);

        // Window Title Bar
        sf::RectangleShape titleBar(sf::Vector2f(subWin.w, 40.0f));
        titleBar.setPosition(subWin.x, subWin.y);
        titleBar.setFillColor(sf::Color(18, 48, 100, 255));
        window.draw(titleBar);

        std::string winTitle = (subWin.type == 1) ? "STACK VISUALIZER (ARRAY-BASED LIFO)" : "QUEUE VISUALIZER (CIRCULAR ARRAY FIFO)";
        sf::Text tText;
        tText.setFont(titleFont);
        tText.setString(winTitle);
        tText.setCharacterSize(16);
        tText.setFillColor(subWin.type == 1 ? sf::Color(255, 230, 70) : sf::Color(80, 235, 255));
        tText.setPosition(subWin.x + 16.0f, subWin.y + 11.0f);
        window.draw(tText);

        // Minimize Button: [-]
        minBtnRect = sf::FloatRect(subWin.x + subWin.w - 74.0f, subWin.y + 6.0f, 30.0f, 28.0f);
        sf::RectangleShape minBox(sf::Vector2f(30.0f, 28.0f));
        minBox.setPosition(minBtnRect.left, minBtnRect.top);
        minBox.setFillColor(sf::Color(35, 75, 135));
        minBox.setOutlineColor(sf::Color(90, 175, 255));
        minBox.setOutlineThickness(1.0f);
        window.draw(minBox);

        sf::Text minText;
        minText.setFont(font);
        minText.setString(subWin.minimized ? "+" : "-");
        minText.setCharacterSize(22);
        minText.setFillColor(sf::Color::White);
        minText.setPosition(minBtnRect.left + (subWin.minimized ? 8.0f : 10.0f), minBtnRect.top);
        window.draw(minText);

        // Close Button: [X]
        closeBtnRect = sf::FloatRect(subWin.x + subWin.w - 38.0f, subWin.y + 6.0f, 30.0f, 28.0f);
        sf::RectangleShape closeBox(sf::Vector2f(30.0f, 28.0f));
        closeBox.setPosition(closeBtnRect.left, closeBtnRect.top);
        closeBox.setFillColor(sf::Color(185, 42, 42));
        closeBox.setOutlineColor(sf::Color(255, 110, 110));
        closeBox.setOutlineThickness(1.0f);
        window.draw(closeBox);

        sf::Text closeText;
        closeText.setFont(font);
        closeText.setString("X");
        closeText.setCharacterSize(18);
        closeText.setFillColor(sf::Color::White);
        closeText.setPosition(closeBtnRect.left + 8.0f, closeBtnRect.top + 3.0f);
        window.draw(closeText);

        if (subWin.minimized) return;

        // Render contents based on type
        if (subWin.type == 1) {
            // STACK VISUALIZATION (Main Array + Other/Aux Array)
            sf::Text h1;
            h1.setFont(font);
            h1.setString("STACK A (MAIN ARRAY) - LIFO MEMORY CELLS");
            h1.setCharacterSize(18);
            h1.setFillColor(sf::Color(90, 200, 255));
            h1.setPosition(subWin.x + 26.0f, subWin.y + 48.0f);
            window.draw(h1);

            sf::Text topInfo;
            topInfo.setFont(font);
            std::string tStr = (mainTop >= 0) ? ("TOP INDEX = " + std::to_string(mainTop)) : "TOP = -1 (EMPTY)";
            topInfo.setString(tStr);
            topInfo.setCharacterSize(16);
            topInfo.setFillColor(mainTop >= 0 ? sf::Color(255, 230, 70) : sf::Color(180, 190, 205));
            topInfo.setPosition(subWin.x + 560.0f, subWin.y + 48.0f);
            window.draw(topInfo);

            float cellW = 84.0f;
            float cellH = 52.0f;
            float startX = subWin.x + 26.0f;
            float curY = subWin.y + 74.0f;

            for (int i = 0; i < 8; i++) {
                float cx = startX + i * (cellW + 5.0f);

                // Index header
                sf::Text idxText;
                idxText.setFont(font);
                idxText.setString("[" + std::to_string(i) + "]");
                idxText.setCharacterSize(14);
                idxText.setFillColor(i == mainTop ? sf::Color(255, 230, 70) : sf::Color(140, 175, 215));
                idxText.setPosition(cx + 30.0f, curY);
                window.draw(idxText);

                // Cell box
                sf::RectangleShape cell(sf::Vector2f(cellW, cellH));
                cell.setPosition(cx, curY + 20.0f);

                bool occupied = (i <= mainTop && mainTop >= 0);
                if (occupied) {
                    cell.setFillColor(i == mainTop ? sf::Color(35, 95, 175, 240) : sf::Color(22, 60, 115, 220));
                    cell.setOutlineColor(i == mainTop ? sf::Color(255, 230, 70) : sf::Color(65, 140, 220));
                    cell.setOutlineThickness(i == mainTop ? 2.5f : 1.5f);
                } else {
                    cell.setFillColor(sf::Color(12, 22, 44, 180));
                    cell.setOutlineColor(sf::Color(40, 70, 115, 120));
                    cell.setOutlineThickness(1.0f);
                }
                window.draw(cell);

                // Cell content
                sf::Text valText;
                valText.setFont(font);
                std::string label = occupied ? mainStack[i] : "---";
                if (label.length() > 9) label = label.substr(0, 8) + ".";
                valText.setString(label);
                valText.setCharacterSize(14);
                valText.setFillColor(occupied ? (i == mainTop ? sf::Color(255, 245, 130) : sf::Color::White) : sf::Color(100, 130, 160));
                valText.setPosition(cx + 6.0f, curY + 36.0f);
                window.draw(valText);

                // Top indicator
                if (i == mainTop) {
                    sf::Text topTag;
                    topTag.setFont(font);
                    topTag.setString("^ TOP");
                    topTag.setCharacterSize(14);
                    topTag.setFillColor(sf::Color(255, 230, 70));
                    topTag.setPosition(cx + 22.0f, curY + 76.0f);
                    window.draw(topTag);
                }
            }

            // STACK B (OTHER / AUXILIARY STACK ARRAY)
            float auxY = subWin.y + 195.0f;
            sf::Text h2;
            h2.setFont(font);
            h2.setString("STACK B (OTHER / AUXILIARY STACK ARRAY)");
            h2.setCharacterSize(18);
            h2.setFillColor(sf::Color(220, 130, 255));
            h2.setPosition(subWin.x + 26.0f, auxY);
            window.draw(h2);

            sf::Text auxInfo;
            auxInfo.setFont(font);
            std::string aStr = (auxTop >= 0) ? ("AUX TOP = " + std::to_string(auxTop)) : "AUX = -1 (EMPTY)";
            auxInfo.setString(aStr);
            auxInfo.setCharacterSize(16);
            auxInfo.setFillColor(auxTop >= 0 ? sf::Color(255, 150, 240) : sf::Color(180, 190, 205));
            auxInfo.setPosition(subWin.x + 560.0f, auxY);
            window.draw(auxInfo);

            float auxCurY = auxY + 26.0f;
            for (int i = 0; i < 8; i++) {
                float cx = startX + i * (cellW + 5.0f);

                // Index header
                sf::Text idxText;
                idxText.setFont(font);
                idxText.setString("[" + std::to_string(i) + "]");
                idxText.setCharacterSize(14);
                idxText.setFillColor(i == auxTop ? sf::Color(255, 150, 240) : sf::Color(170, 140, 200));
                idxText.setPosition(cx + 30.0f, auxCurY);
                window.draw(idxText);

                // Cell box
                sf::RectangleShape cell(sf::Vector2f(cellW, cellH));
                cell.setPosition(cx, auxCurY + 20.0f);

                bool occupied = (i <= auxTop && auxTop >= 0);
                if (occupied) {
                    cell.setFillColor(i == auxTop ? sf::Color(95, 35, 125, 240) : sf::Color(65, 25, 85, 220));
                    cell.setOutlineColor(i == auxTop ? sf::Color(255, 140, 245) : sf::Color(150, 65, 190));
                    cell.setOutlineThickness(i == auxTop ? 2.5f : 1.5f);
                } else {
                    cell.setFillColor(sf::Color(20, 14, 34, 180));
                    cell.setOutlineColor(sf::Color(65, 45, 90, 120));
                    cell.setOutlineThickness(1.0f);
                }
                window.draw(cell);

                // Cell content
                sf::Text valText;
                valText.setFont(font);
                std::string label = occupied ? auxStack[i] : "---";
                if (label.length() > 9) label = label.substr(0, 8) + ".";
                valText.setString(label);
                valText.setCharacterSize(14);
                valText.setFillColor(occupied ? (i == auxTop ? sf::Color(255, 200, 255) : sf::Color::White) : sf::Color(120, 100, 140));
                valText.setPosition(cx + 6.0f, auxCurY + 36.0f);
                window.draw(valText);

                // Aux Top indicator
                if (i == auxTop) {
                    sf::Text topTag;
                    topTag.setFont(font);
                    topTag.setString("^ TOP");
                    topTag.setCharacterSize(14);
                    topTag.setFillColor(sf::Color(255, 150, 240));
                    topTag.setPosition(cx + 22.0f, auxCurY + 76.0f);
                    window.draw(topTag);
                }
            }

            // Info and Animation Status Panel
            sf::RectangleShape infoBox(sf::Vector2f(708.0f, 110.0f));
            infoBox.setPosition(subWin.x + 26.0f, subWin.y + 355.0f);
            infoBox.setFillColor(sf::Color(12, 22, 46, 230));
            infoBox.setOutlineColor(sf::Color(55, 125, 200, 200));
            infoBox.setOutlineThickness(1.5f);
            window.draw(infoBox);

            sf::Text sTitle;
            sTitle.setFont(font);
            sTitle.setString(">> OPERATION STATUS:");
            sTitle.setCharacterSize(16);
            sTitle.setFillColor(sf::Color(255, 225, 60));
            sTitle.setPosition(subWin.x + 40.0f, subWin.y + 365.0f);
            window.draw(sTitle);

            sf::Text sMsg;
            sMsg.setFont(font);
            sMsg.setString(statusMsg.empty() ? "Idle - Click 'ANIMATE DATA STRUCTURES' to test pop/push cycle." : statusMsg);
            sMsg.setCharacterSize(18);
            sMsg.setFillColor(sf::Color(240, 245, 255));
            sMsg.setPosition(subWin.x + 40.0f, subWin.y + 392.0f);
            window.draw(sMsg);

            sf::Text sDesc;
            sDesc.setFont(font);
            sDesc.setString("LIFO Law: Elements pop from Stack A, transfer into Stack B, and re-push back to refill!");
            sDesc.setCharacterSize(14);
            sDesc.setFillColor(sf::Color(130, 180, 230));
            sDesc.setPosition(subWin.x + 40.0f, subWin.y + 430.0f);
            window.draw(sDesc);

        } else if (subWin.type == 2) {
            // QUEUE VISUALIZATION (Circular Array)
            sf::Text h1;
            h1.setFont(font);
            h1.setString("CIRCULAR QUEUE ARRAY (FIFO) - 8 FIXED SLOTS");
            h1.setCharacterSize(18);
            h1.setFillColor(sf::Color(70, 235, 205));
            h1.setPosition(subWin.x + 26.0f, subWin.y + 50.0f);
            window.draw(h1);

            sf::Text qMeta;
            qMeta.setFont(font);
            qMeta.setString("COUNT: " + std::to_string(queueCount) + "/8  |  FRONT: " + std::to_string(queueFront) + "  |  REAR: " + std::to_string(queueRear));
            qMeta.setCharacterSize(16);
            qMeta.setFillColor(sf::Color(255, 230, 70));
            qMeta.setPosition(subWin.x + 460.0f, subWin.y + 50.0f);
            window.draw(qMeta);

            float cellW = 84.0f;
            float cellH = 64.0f;
            float startX = subWin.x + 26.0f;
            float curY = subWin.y + 110.0f;

            for (int i = 0; i < 8; i++) {
                float cx = startX + i * (cellW + 5.0f);

                // Front indicator
                if (queueCount > 0 && i == queueFront) {
                    sf::Text frontTag;
                    frontTag.setFont(font);
                    frontTag.setString("v FRONT");
                    frontTag.setCharacterSize(14);
                    frontTag.setFillColor(sf::Color(70, 235, 205));
                    frontTag.setPosition(cx + 16.0f, curY - 24.0f);
                    window.draw(frontTag);
                }

                // Index header
                sf::Text idxText;
                idxText.setFont(font);
                idxText.setString("[" + std::to_string(i) + "]");
                idxText.setCharacterSize(14);
                idxText.setFillColor(sf::Color(140, 200, 215));
                idxText.setPosition(cx + 30.0f, curY);
                window.draw(idxText);

                // Cell box
                sf::RectangleShape cell(sf::Vector2f(cellW, cellH));
                cell.setPosition(cx, curY + 20.0f);

                // Check circular occupancy
                bool isOccupied = false;
                if (queueCount > 0) {
                    int offset = (i - queueFront + 8) % 8;
                    if (offset < queueCount) isOccupied = true;
                }

                if (isOccupied) {
                    cell.setFillColor(i == queueFront ? sf::Color(20, 95, 85, 240) : sf::Color(15, 65, 60, 220));
                    cell.setOutlineColor(i == queueFront ? sf::Color(70, 240, 210) : sf::Color(45, 170, 150));
                    cell.setOutlineThickness(i == queueFront ? 2.5f : 1.5f);
                } else {
                    cell.setFillColor(sf::Color(10, 24, 28, 180));
                    cell.setOutlineColor(sf::Color(35, 65, 75, 120));
                    cell.setOutlineThickness(1.0f);
                }
                window.draw(cell);

                // Cell content
                sf::Text valText;
                valText.setFont(font);
                std::string label = isOccupied ? queueArr[i] : "---";
                if (label.length() > 9) label = label.substr(0, 8) + ".";
                valText.setString(label);
                valText.setCharacterSize(14);
                valText.setFillColor(isOccupied ? sf::Color(230, 255, 250) : sf::Color(90, 130, 140));
                valText.setPosition(cx + 6.0f, curY + 42.0f);
                window.draw(valText);

                // Rear indicator
                if (queueCount > 0 && i == queueRear) {
                    sf::Text rearTag;
                    rearTag.setFont(font);
                    rearTag.setString("^ REAR");
                    rearTag.setCharacterSize(14);
                    rearTag.setFillColor(sf::Color(255, 185, 60));
                    rearTag.setPosition(cx + 20.0f, curY + 90.0f);
                    window.draw(rearTag);
                }
            }

            // Queue status and mechanics
            sf::RectangleShape infoBox(sf::Vector2f(708.0f, 130.0f));
            infoBox.setPosition(subWin.x + 26.0f, subWin.y + 260.0f);
            infoBox.setFillColor(sf::Color(10, 28, 32, 230));
            infoBox.setOutlineColor(sf::Color(45, 160, 145, 200));
            infoBox.setOutlineThickness(1.5f);
            window.draw(infoBox);

            sf::Text sTitle;
            sTitle.setFont(font);
            sTitle.setString(">> CIRCULAR QUEUE STATE:");
            sTitle.setCharacterSize(16);
            sTitle.setFillColor(sf::Color(255, 225, 60));
            sTitle.setPosition(subWin.x + 40.0f, subWin.y + 275.0f);
            window.draw(sTitle);

            sf::Text sMsg;
            sMsg.setFont(font);
            sMsg.setString(statusMsg.empty() ? "Queue Ready - Operations processed in FIFO arrival order." : statusMsg);
            sMsg.setCharacterSize(18);
            sMsg.setFillColor(sf::Color(240, 255, 250));
            sMsg.setPosition(subWin.x + 40.0f, subWin.y + 305.0f);
            window.draw(sMsg);

            sf::Text sDesc;
            sDesc.setFont(font);
            sDesc.setString("FIFO Law: Jobs enqueue at REAR and dequeue from FRONT in O(1) time without element shifting!");
            sDesc.setCharacterSize(14);
            sDesc.setFillColor(sf::Color(120, 210, 195));
            sDesc.setPosition(subWin.x + 40.0f, subWin.y + 345.0f);
            window.draw(sDesc);
        }
    }

}
