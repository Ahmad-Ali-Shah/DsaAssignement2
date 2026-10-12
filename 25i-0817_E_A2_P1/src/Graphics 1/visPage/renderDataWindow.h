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
        (void)statusMsg;
        if (!subWin.visible) return;

        float winW = static_cast<float>(window.getSize().x);
        subWin.w = 760.0f;
        subWin.h = subWin.minimized ? 42.0f : 500.0f;
        subWin.x = (winW - subWin.w) / 2.0f;
        subWin.y = subWin.minimized ? 660.0f : 110.0f;

        // Dim background overlay when expanded
        if (!subWin.minimized) {
            sf::RectangleShape dim(sf::Vector2f(winW, static_cast<float>(window.getSize().y)));
            dim.setFillColor(sf::Color(0, 0, 0, 165));
            window.draw(dim);
        }

        // Subwindow frame: Deep blue background with cyber arcade glow
        sf::RectangleShape box(sf::Vector2f(subWin.w, subWin.h));
        box.setPosition(subWin.x, subWin.y);
        box.setFillColor(sf::Color(10, 24, 52, 250));
        box.setOutlineColor(subWin.type == 1 ? sf::Color(55, 140, 240) : sf::Color(45, 190, 170));
        box.setOutlineThickness(3.0f);
        window.draw(box);

        // Window Title Bar
        sf::RectangleShape titleBar(sf::Vector2f(subWin.w, 40.0f));
        titleBar.setPosition(subWin.x, subWin.y);
        titleBar.setFillColor(subWin.type == 1 ? sf::Color(18, 48, 100) : sf::Color(15, 60, 65));
        window.draw(titleBar);

        std::string winTitle = (subWin.type == 1) ? "STACK VISUALIZER (ARRAY LIFO)" : "QUEUE VISUALIZER (CIRCULAR ARRAY FIFO)";
        sf::Text tText;
        tText.setFont(titleFont);
        tText.setString(winTitle);
        tText.setCharacterSize(16);
        tText.setFillColor(subWin.type == 1 ? sf::Color(255, 230, 70) : sf::Color(80, 240, 220));
        tText.setPosition(subWin.x + 16.0f, subWin.y + 11.0f);
        window.draw(tText);

        // Minimize Button: [-]
        minBtnRect = sf::FloatRect(subWin.x + subWin.w - 76.0f, subWin.y + 7.0f, 28.0f, 26.0f);
        sf::RectangleShape minBox(sf::Vector2f(28.0f, 26.0f));
        minBox.setPosition(minBtnRect.left, minBtnRect.top);
        minBox.setFillColor(sf::Color(35, 75, 135));
        minBox.setOutlineColor(sf::Color(90, 175, 255));
        minBox.setOutlineThickness(1.0f);
        window.draw(minBox);

        sf::Text minText;
        minText.setFont(font);
        minText.setString(subWin.minimized ? "+" : "-");
        minText.setCharacterSize(20);
        minText.setFillColor(sf::Color::White);
        sf::FloatRect mtb = minText.getLocalBounds();
        minText.setOrigin(mtb.left + mtb.width / 2.0f, mtb.top + mtb.height / 2.0f);
        minText.setPosition(minBtnRect.left + 14.0f, minBtnRect.top + 13.0f);
        window.draw(minText);

        // Close Button: [X] - inset properly away from right border
        closeBtnRect = sf::FloatRect(subWin.x + subWin.w - 42.0f, subWin.y + 7.0f, 28.0f, 26.0f);
        sf::RectangleShape closeBox(sf::Vector2f(28.0f, 26.0f));
        closeBox.setPosition(closeBtnRect.left, closeBtnRect.top);
        closeBox.setFillColor(sf::Color(185, 42, 42));
        closeBox.setOutlineColor(sf::Color(255, 110, 110));
        closeBox.setOutlineThickness(1.0f);
        window.draw(closeBox);

        sf::Text closeText;
        closeText.setFont(font);
        closeText.setString("X");
        closeText.setCharacterSize(16);
        closeText.setFillColor(sf::Color::White);
        sf::FloatRect ctb = closeText.getLocalBounds();
        closeText.setOrigin(ctb.left + ctb.width / 2.0f, ctb.top + ctb.height / 2.0f);
        closeText.setPosition(closeBtnRect.left + 14.0f, closeBtnRect.top + 13.0f);
        window.draw(closeText);

        if (subWin.minimized) return;

        // Render contents based on type
        if (subWin.type == 1) {
            // ================= STACK MODE =================
            sf::Text h1;
            h1.setFont(font);
            h1.setString("STACK A (MAIN ARRAY)");
            h1.setCharacterSize(16);
            h1.setFillColor(sf::Color(90, 200, 255));
            h1.setPosition(subWin.x + 26.0f, subWin.y + 46.0f);
            window.draw(h1);

            float cellW = 84.0f;
            float cellH = 46.0f;
            float startX = subWin.x + 26.0f;
            float curY = subWin.y + 66.0f;

            for (int i = 0; i < 8; i++) {
                float cx = startX + i * (cellW + 5.0f);

                // Index header
                sf::Text idxText;
                idxText.setFont(font);
                idxText.setString("[" + std::to_string(i) + "]");
                idxText.setCharacterSize(13);
                idxText.setFillColor(i == mainTop ? sf::Color(255, 230, 70) : sf::Color(140, 175, 215));
                idxText.setPosition(cx + 30.0f, curY);
                window.draw(idxText);

                // Cell box
                sf::RectangleShape cell(sf::Vector2f(cellW, cellH));
                cell.setPosition(cx, curY + 16.0f);

                bool occupied = (i <= mainTop && mainTop >= 0);
                if (occupied) {
                    cell.setFillColor(i == mainTop ? sf::Color(35, 95, 175, 240) : sf::Color(22, 60, 115, 220));
                    cell.setOutlineColor(i == mainTop ? sf::Color(255, 230, 70) : sf::Color(65, 140, 220));
                    cell.setOutlineThickness(i == mainTop ? 2.0f : 1.0f);
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
                valText.setCharacterSize(13);
                valText.setFillColor(occupied ? (i == mainTop ? sf::Color(255, 245, 130) : sf::Color::White) : sf::Color(100, 130, 160));
                valText.setPosition(cx + 6.0f, curY + 30.0f);
                window.draw(valText);

                // Top indicator
                if (i == mainTop) {
                    sf::Text topTag;
                    topTag.setFont(font);
                    topTag.setString("^ TOP");
                    topTag.setCharacterSize(13);
                    topTag.setFillColor(sf::Color(255, 230, 70));
                    topTag.setPosition(cx + 22.0f, curY + 64.0f);
                    window.draw(topTag);
                }
            }

            // STACK B (AUXILIARY ARRAY)
            float auxY = subWin.y + 168.0f;
            sf::Text h2;
            h2.setFont(font);
            h2.setString("STACK B (OTHER / AUXILIARY ARRAY)");
            h2.setCharacterSize(16);
            h2.setFillColor(sf::Color(220, 130, 255));
            h2.setPosition(subWin.x + 26.0f, auxY);
            window.draw(h2);

            float auxCurY = auxY + 20.0f;
            for (int i = 0; i < 8; i++) {
                float cx = startX + i * (cellW + 5.0f);

                // Index header
                sf::Text idxText;
                idxText.setFont(font);
                idxText.setString("[" + std::to_string(i) + "]");
                idxText.setCharacterSize(13);
                idxText.setFillColor(i == auxTop ? sf::Color(255, 150, 240) : sf::Color(170, 140, 200));
                idxText.setPosition(cx + 30.0f, auxCurY);
                window.draw(idxText);

                // Cell box
                sf::RectangleShape cell(sf::Vector2f(cellW, cellH));
                cell.setPosition(cx, auxCurY + 16.0f);

                bool occupied = (i <= auxTop && auxTop >= 0);
                if (occupied) {
                    cell.setFillColor(i == auxTop ? sf::Color(95, 35, 125, 240) : sf::Color(65, 25, 85, 220));
                    cell.setOutlineColor(i == auxTop ? sf::Color(255, 140, 245) : sf::Color(150, 65, 190));
                    cell.setOutlineThickness(i == auxTop ? 2.0f : 1.0f);
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
                valText.setCharacterSize(13);
                valText.setFillColor(occupied ? (i == auxTop ? sf::Color(255, 200, 255) : sf::Color::White) : sf::Color(120, 100, 140));
                valText.setPosition(cx + 6.0f, auxCurY + 30.0f);
                window.draw(valText);

                // Aux Top indicator
                if (i == auxTop) {
                    sf::Text topTag;
                    topTag.setFont(font);
                    topTag.setString("^ TOP");
                    topTag.setCharacterSize(13);
                    topTag.setFillColor(sf::Color(255, 150, 240));
                    topTag.setPosition(cx + 22.0f, auxCurY + 64.0f);
                    window.draw(topTag);
                }
            }

            // ================= DRY RUN TRACE TABLE =================
            float tblY = subWin.y + 282.0f;
            float tblW = 708.0f;
            float tblH = 195.0f;

            // Outer border
            sf::RectangleShape tblBox(sf::Vector2f(tblW, tblH));
            tblBox.setPosition(startX, tblY);
            tblBox.setFillColor(sf::Color(8, 18, 38, 240));
            tblBox.setOutlineColor(sf::Color(55, 120, 205));
            tblBox.setOutlineThickness(1.5f);
            window.draw(tblBox);

            // Table Header Row
            sf::RectangleShape thBox(sf::Vector2f(tblW, 28.0f));
            thBox.setPosition(startX, tblY);
            thBox.setFillColor(sf::Color(18, 45, 88));
            window.draw(thBox);

            auto drawText = [&](const std::string& str, float tx, float ty, sf::Color clr, int sz = 14) {
                sf::Text t;
                t.setFont(font);
                t.setString(str);
                t.setCharacterSize(sz);
                t.setFillColor(clr);
                t.setPosition(tx, ty);
                window.draw(t);
            };

            drawText("VARIABLE", startX + 16.0f, tblY + 5.0f, sf::Color(255, 225, 70), 14);
            drawText("CURRENT VALUE", startX + 210.0f, tblY + 5.0f, sf::Color(255, 225, 70), 14);
            drawText("TRACE / POINTER MEANING", startX + 410.0f, tblY + 5.0f, sf::Color(255, 225, 70), 14);

            // Data rows
            std::string rows[5][3] = {
                {"TOP (Stack A)", mainTop >= 0 ? ("Index " + std::to_string(mainTop)) : "-1 (EMPTY)", "Points to active top element in Stack A"},
                {"SIZE (Stack A)", std::to_string(mainTop + 1) + " / 8 Elements", "Number of valid operations in LIFO stack"},
                {"PEEK TOP", mainTop >= 0 ? mainStack[mainTop] : "None (EMPTY)", "Element accessed by top() in O(1)"},
                {"TOP (Stack B)", auxTop >= 0 ? ("Index " + std::to_string(auxTop)) : "-1 (EMPTY)", "Auxiliary stack used for pop-repush transfer"},
                {"NEXT ACTION", "Pop stackA[TOP] -> Push", "LIFO: Element pops from A and pushes into B"}
            };

            float rowH = 32.0f;
            for (int r = 0; r < 5; r++) {
                float ry = tblY + 28.0f + r * rowH;
                sf::RectangleShape rBox(sf::Vector2f(tblW, rowH));
                rBox.setPosition(startX, ry);
                rBox.setFillColor((r % 2 == 0) ? sf::Color(12, 24, 48, 200) : sf::Color(8, 16, 36, 200));
                window.draw(rBox);

                // Subtle grid line
                sf::RectangleShape line(sf::Vector2f(tblW, 1.0f));
                line.setPosition(startX, ry + rowH);
                line.setFillColor(sf::Color(35, 70, 120, 100));
                window.draw(line);

                drawText(rows[r][0], startX + 16.0f, ry + 7.0f, sf::Color(140, 200, 255), 14);
                drawText(rows[r][1], startX + 210.0f, ry + 7.0f, sf::Color(255, 240, 140), 14);
                drawText(rows[r][2], startX + 410.0f, ry + 7.0f, sf::Color(200, 215, 235), 14);
            }

        } else if (subWin.type == 2) {
            // ================= QUEUE MODE =================
            sf::Text h1;
            h1.setFont(font);
            h1.setString("CIRCULAR QUEUE ARRAY (8 FIXED SLOTS)");
            h1.setCharacterSize(16);
            h1.setFillColor(sf::Color(70, 235, 205));
            h1.setPosition(subWin.x + 26.0f, subWin.y + 46.0f);
            window.draw(h1);

            float cellW = 84.0f;
            float cellH = 58.0f;
            float startX = subWin.x + 26.0f;
            float curY = subWin.y + 88.0f;

            for (int i = 0; i < 8; i++) {
                float cx = startX + i * (cellW + 5.0f);

                // Front indicator
                if (queueCount > 0 && i == queueFront) {
                    sf::Text frontTag;
                    frontTag.setFont(font);
                    frontTag.setString("v FRONT");
                    frontTag.setCharacterSize(13);
                    frontTag.setFillColor(sf::Color(70, 235, 205));
                    frontTag.setPosition(cx + 16.0f, curY - 20.0f);
                    window.draw(frontTag);
                }

                // Index header
                sf::Text idxText;
                idxText.setFont(font);
                idxText.setString("[" + std::to_string(i) + "]");
                idxText.setCharacterSize(13);
                idxText.setFillColor(sf::Color(140, 200, 215));
                idxText.setPosition(cx + 30.0f, curY);
                window.draw(idxText);

                // Cell box
                sf::RectangleShape cell(sf::Vector2f(cellW, cellH));
                cell.setPosition(cx, curY + 16.0f);

                bool isOccupied = false;
                if (queueCount > 0) {
                    int offset = (i - queueFront + 8) % 8;
                    if (offset < queueCount) isOccupied = true;
                }

                if (isOccupied) {
                    cell.setFillColor(i == queueFront ? sf::Color(20, 95, 85, 240) : sf::Color(15, 65, 60, 220));
                    cell.setOutlineColor(i == queueFront ? sf::Color(70, 240, 210) : sf::Color(45, 170, 150));
                    cell.setOutlineThickness(i == queueFront ? 2.0f : 1.0f);
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
                valText.setCharacterSize(13);
                valText.setFillColor(isOccupied ? sf::Color(230, 255, 250) : sf::Color(90, 130, 140));
                valText.setPosition(cx + 6.0f, curY + 36.0f);
                window.draw(valText);

                // Rear indicator
                if (queueCount > 0 && i == queueRear) {
                    sf::Text rearTag;
                    rearTag.setFont(font);
                    rearTag.setString("^ REAR");
                    rearTag.setCharacterSize(13);
                    rearTag.setFillColor(sf::Color(255, 185, 60));
                    rearTag.setPosition(cx + 20.0f, curY + 78.0f);
                    window.draw(rearTag);
                }
            }

            // ================= DRY RUN TRACE TABLE =================
            float tblY = subWin.y + 205.0f;
            float tblW = 708.0f;
            float tblH = 265.0f;

            // Outer border
            sf::RectangleShape tblBox(sf::Vector2f(tblW, tblH));
            tblBox.setPosition(startX, tblY);
            tblBox.setFillColor(sf::Color(8, 22, 26, 240));
            tblBox.setOutlineColor(sf::Color(45, 160, 145));
            tblBox.setOutlineThickness(1.5f);
            window.draw(tblBox);

            // Table Header Row
            sf::RectangleShape thBox(sf::Vector2f(tblW, 30.0f));
            thBox.setPosition(startX, tblY);
            thBox.setFillColor(sf::Color(14, 52, 55));
            window.draw(thBox);

            auto drawText = [&](const std::string& str, float tx, float ty, sf::Color clr, int sz = 14) {
                sf::Text t;
                t.setFont(font);
                t.setString(str);
                t.setCharacterSize(sz);
                t.setFillColor(clr);
                t.setPosition(tx, ty);
                window.draw(t);
            };

            drawText("VARIABLE", startX + 16.0f, tblY + 6.0f, sf::Color(255, 225, 70), 14);
            drawText("CURRENT VALUE", startX + 210.0f, tblY + 6.0f, sf::Color(255, 225, 70), 14);
            drawText("TRACE / POINTER MEANING", startX + 410.0f, tblY + 6.0f, sf::Color(255, 225, 70), 14);

            int nextSlot = (queueRear + 1) % 8;
            std::string frontVal = (queueCount > 0 ? queueArr[queueFront] : "None (EMPTY)");
            std::string rearVal = (queueCount > 0 ? queueArr[queueRear] : "None (EMPTY)");

            std::string qRows[7][3] = {
                {"FRONT Index", "Index " + std::to_string(queueFront), "Points to element removed next by deleteQueue()"},
                {"REAR Index", "Index " + std::to_string(queueRear), "Points to most recently added element in queue"},
                {"COUNT", std::to_string(queueCount) + " / 8 Slots", "Current number of stored jobs in circular array"},
                {"PEEK FRONT", frontVal, "Element accessed by front() in O(1)"},
                {"PEEK REAR", rearVal, "Element accessed by back() in O(1)"},
                {"NEXT ENQUEUE AT", "Index " + std::to_string(nextSlot), "Calculated via circular formula: (REAR + 1) % 8"},
                {"CIRCULAR LAW", "O(1) No Shifting", "Circular modulo wraps around without moving array cells"}
            };

            float rowH = 33.0f;
            for (int r = 0; r < 7; r++) {
                float ry = tblY + 30.0f + r * rowH;
                sf::RectangleShape rBox(sf::Vector2f(tblW, rowH));
                rBox.setPosition(startX, ry);
                rBox.setFillColor((r % 2 == 0) ? sf::Color(10, 30, 35, 200) : sf::Color(7, 20, 24, 200));
                window.draw(rBox);

                // Subtle grid line
                sf::RectangleShape line(sf::Vector2f(tblW, 1.0f));
                line.setPosition(startX, ry + rowH);
                line.setFillColor(sf::Color(30, 80, 75, 100));
                window.draw(line);

                drawText(qRows[r][0], startX + 16.0f, ry + 8.0f, sf::Color(110, 230, 210), 14);
                drawText(qRows[r][1], startX + 210.0f, ry + 8.0f, sf::Color(255, 235, 120), 14);
                drawText(qRows[r][2], startX + 410.0f, ry + 8.0f, sf::Color(210, 245, 240), 14);
            }
        }
    }

}
