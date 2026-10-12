#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace EditorPage {

    struct RightButtonRects {
        sf::FloatRect reloadBtn;
        sf::FloatRect saveBtn;
        sf::FloatRect savePathBox;
        sf::FloatRect undoBtn;
        sf::FloatRect redoBtn;
        sf::FloatRect backBtn;
    };

    void renderRightPanel(sf::RenderWindow& window, const sf::Font& font, float mouseX, float mouseY, const std::string& savePath, bool isTypingSave, RightButtonRects& rects) {
        float winW = static_cast<float>(window.getSize().x);
        float startX = winW - 310.0f;
        float curY = 24.0f;
        float panelW = 286.0f;

        // Title: ACTIONS & EXPORT
        sf::Text title;
        title.setFont(font);
        title.setString("ACTIONS & EXPORT");
        title.setCharacterSize(22);
        title.setFillColor(sf::Color(255, 228, 50));
        title.setPosition(startX, curY);
        window.draw(title);
        curY += 32.0f;

        // 1. Back to Home / Main Menu Button
        rects.backBtn = sf::FloatRect(startX, curY, panelW, 36.0f);
        bool hBack = rects.backBtn.contains(mouseX, mouseY);
        sf::RectangleShape bBox(sf::Vector2f(panelW, 36.0f));
        bBox.setPosition(startX, curY);
        bBox.setFillColor(hBack ? sf::Color(135, 45, 55, 240) : sf::Color(85, 28, 36, 220));
        bBox.setOutlineColor(hBack ? sf::Color(255, 225, 80) : sf::Color(210, 80, 95, 210));
        bBox.setOutlineThickness(hBack ? 2.0f : 1.5f);
        window.draw(bBox);

        sf::Text bText;
        bText.setFont(font);
        bText.setString("<-- BACK TO MAIN MENU");
        bText.setCharacterSize(17);
        bText.setFillColor(hBack ? sf::Color(255, 245, 120) : sf::Color(250, 230, 235));
        sf::FloatRect btb = bText.getLocalBounds();
        bText.setOrigin(btb.left + btb.width / 2.0f, btb.top + btb.height / 2.0f);
        bText.setPosition(startX + panelW / 2.0f, curY + 18.0f);
        window.draw(bText);
        curY += 46.0f;

        // 2. Reload Button
        rects.reloadBtn = sf::FloatRect(startX, curY, panelW, 40.0f);
        bool hReload = rects.reloadBtn.contains(mouseX, mouseY);
        sf::RectangleShape relBox(sf::Vector2f(panelW, 40.0f));
        relBox.setPosition(startX, curY);
        relBox.setFillColor(hReload ? sf::Color(45, 65, 85, 230) : sf::Color(25, 35, 48, 210));
        relBox.setOutlineColor(hReload ? sf::Color(255, 225, 50) : sf::Color(70, 100, 130, 200));
        relBox.setOutlineThickness(hReload ? 2.0f : 1.5f);
        window.draw(relBox);

        sf::Text relText;
        relText.setFont(font);
        relText.setString("RELOAD ORIGINAL IMAGE");
        relText.setCharacterSize(17);
        relText.setFillColor(hReload ? sf::Color(255, 235, 80) : sf::Color(220, 235, 245));
        sf::FloatRect rtb = relText.getLocalBounds();
        relText.setOrigin(rtb.left + rtb.width / 2.0f, rtb.top + rtb.height / 2.0f);
        relText.setPosition(startX + panelW / 2.0f, curY + 20.0f);
        window.draw(relText);
        curY += 48.0f;

        // 3. Undo / Redo Buttons
        float halfW = (panelW - 10.0f) / 2.0f;
        rects.undoBtn = sf::FloatRect(startX, curY, halfW, 36.0f);
        bool hUndo = rects.undoBtn.contains(mouseX, mouseY);
        sf::RectangleShape uBox(sf::Vector2f(halfW, 36.0f));
        uBox.setPosition(startX, curY);
        uBox.setFillColor(hUndo ? sf::Color(45, 65, 85, 230) : sf::Color(25, 35, 48, 210));
        uBox.setOutlineColor(hUndo ? sf::Color(255, 225, 50) : sf::Color(70, 100, 130, 200));
        uBox.setOutlineThickness(1.5f);
        window.draw(uBox);

        sf::Text uText;
        uText.setFont(font);
        uText.setString("UNDO");
        uText.setCharacterSize(16);
        uText.setFillColor(hUndo ? sf::Color(255, 235, 80) : sf::Color(220, 235, 245));
        sf::FloatRect utb = uText.getLocalBounds();
        uText.setOrigin(utb.left + utb.width / 2.0f, utb.top + utb.height / 2.0f);
        uText.setPosition(startX + halfW / 2.0f, curY + 18.0f);
        window.draw(uText);

        rects.redoBtn = sf::FloatRect(startX + halfW + 10.0f, curY, halfW, 36.0f);
        bool hRedo = rects.redoBtn.contains(mouseX, mouseY);
        sf::RectangleShape rBox(sf::Vector2f(halfW, 36.0f));
        rBox.setPosition(startX + halfW + 10.0f, curY);
        rBox.setFillColor(hRedo ? sf::Color(45, 65, 85, 230) : sf::Color(25, 35, 48, 210));
        rBox.setOutlineColor(hRedo ? sf::Color(255, 225, 50) : sf::Color(70, 100, 130, 200));
        rBox.setOutlineThickness(1.5f);
        window.draw(rBox);

        sf::Text rText;
        rText.setFont(font);
        rText.setString("REDO");
        rText.setCharacterSize(16);
        rText.setFillColor(hRedo ? sf::Color(255, 235, 80) : sf::Color(220, 235, 245));
        sf::FloatRect redoTb = rText.getLocalBounds();
        rText.setOrigin(redoTb.left + redoTb.width / 2.0f, redoTb.top + redoTb.height / 2.0f);
        rText.setPosition(startX + halfW + 10.0f + halfW / 2.0f, curY + 18.0f);
        window.draw(rText);
        curY += 46.0f;

        // 4. Save Section Card
        sf::RectangleShape saveCard(sf::Vector2f(panelW, 165.0f));
        saveCard.setPosition(startX, curY);
        saveCard.setFillColor(sf::Color(15, 22, 30, 230));
        saveCard.setOutlineColor(sf::Color(80, 130, 180, 220));
        saveCard.setOutlineThickness(2.0f);
        window.draw(saveCard);

        sf::Text sHeader;
        sHeader.setFont(font);
        sHeader.setString("SAVE IMAGE");
        sHeader.setCharacterSize(19);
        sHeader.setFillColor(sf::Color(255, 228, 50));
        sHeader.setPosition(startX + 14.0f, curY + 10.0f);
        window.draw(sHeader);

        sf::Text pLabel;
        pLabel.setFont(font);
        pLabel.setString("Mention Path :");
        pLabel.setCharacterSize(15);
        pLabel.setFillColor(sf::Color(200, 220, 240));
        pLabel.setPosition(startX + 14.0f, curY + 38.0f);
        window.draw(pLabel);

        // Path input box
        rects.savePathBox = sf::FloatRect(startX + 14.0f, curY + 62.0f, panelW - 28.0f, 36.0f);
        sf::RectangleShape pBox(sf::Vector2f(panelW - 28.0f, 36.0f));
        pBox.setPosition(startX + 14.0f, curY + 62.0f);
        pBox.setFillColor(sf::Color(25, 35, 48, 220));
        pBox.setOutlineColor(isTypingSave ? sf::Color(255, 225, 50) : sf::Color(70, 100, 130, 180));
        pBox.setOutlineThickness(isTypingSave ? 2.0f : 1.0f);
        window.draw(pBox);

        sf::Text pVal;
        pVal.setFont(font);
        pVal.setString(savePath + (isTypingSave ? "_" : ""));
        pVal.setCharacterSize(15);
        pVal.setFillColor(sf::Color(255, 255, 255));
        pVal.setPosition(startX + 20.0f, curY + 70.0f);
        window.draw(pVal);

        // Save Action Button
        rects.saveBtn = sf::FloatRect(startX + 14.0f, curY + 110.0f, panelW - 28.0f, 40.0f);
        bool hSave = rects.saveBtn.contains(mouseX, mouseY);
        sf::RectangleShape sBtn(sf::Vector2f(panelW - 28.0f, 40.0f));
        sBtn.setPosition(startX + 14.0f, curY + 110.0f);
        sBtn.setFillColor(hSave ? sf::Color(35, 90, 50, 240) : sf::Color(25, 65, 40, 220));
        sBtn.setOutlineColor(hSave ? sf::Color(255, 235, 80) : sf::Color(80, 180, 100, 200));
        sBtn.setOutlineThickness(hSave ? 2.0f : 1.5f);
        window.draw(sBtn);

        sf::Text sBtnText;
        sBtnText.setFont(font);
        sBtnText.setString("CONFIRM SAVE");
        sBtnText.setCharacterSize(18);
        sBtnText.setFillColor(sf::Color(255, 255, 255));
        sf::FloatRect stb = sBtnText.getLocalBounds();
        sBtnText.setOrigin(stb.left + stb.width / 2.0f, stb.top + stb.height / 2.0f);
        sBtnText.setPosition(startX + panelW / 2.0f, curY + 130.0f);
        window.draw(sBtnText);
    }

}
