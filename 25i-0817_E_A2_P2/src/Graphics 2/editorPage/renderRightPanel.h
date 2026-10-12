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
    };

    void renderRightPanel(sf::RenderWindow& window, const sf::Font& font, float mouseX, float mouseY, const std::string& savePath, bool isTypingSave, RightButtonRects& rects) {
        float winW = static_cast<float>(window.getSize().x);
        float startX = winW - 310.0f;
        float curY = 30.0f;
        float panelW = 286.0f;

        // Title: CONTROLS & SAVE
        sf::Text title;
        title.setFont(font);
        title.setString("ACTIONS & EXPORT");
        title.setCharacterSize(22);
        title.setFillColor(sf::Color(255, 228, 50));
        title.setPosition(startX, curY);
        window.draw(title);
        curY += 36.0f;

        // 1. Reload Button
        rects.reloadBtn = sf::FloatRect(startX, curY, panelW, 44.0f);
        bool hReload = rects.reloadBtn.contains(mouseX, mouseY);
        sf::RectangleShape relBox(sf::Vector2f(panelW, 44.0f));
        relBox.setPosition(startX, curY);
        relBox.setFillColor(hReload ? sf::Color(45, 65, 85, 230) : sf::Color(25, 35, 48, 210));
        relBox.setOutlineColor(hReload ? sf::Color(255, 225, 50) : sf::Color(70, 100, 130, 200));
        relBox.setOutlineThickness(hReload ? 2.0f : 1.5f);
        window.draw(relBox);

        sf::Text relText;
        relText.setFont(font);
        relText.setString("RELOAD ORIGINAL IMAGE");
        relText.setCharacterSize(18);
        relText.setFillColor(hReload ? sf::Color(255, 235, 80) : sf::Color(220, 235, 245));
        relText.setPosition(startX + 24.0f, curY + 12.0f);
        window.draw(relText);
        curY += 56.0f;

        // 2. Undo / Redo Buttons
        float halfW = (panelW - 10.0f) / 2.0f;
        rects.undoBtn = sf::FloatRect(startX, curY, halfW, 38.0f);
        bool hUndo = rects.undoBtn.contains(mouseX, mouseY);
        sf::RectangleShape uBox(sf::Vector2f(halfW, 38.0f));
        uBox.setPosition(startX, curY);
        uBox.setFillColor(hUndo ? sf::Color(45, 65, 85, 230) : sf::Color(25, 35, 48, 210));
        uBox.setOutlineColor(hUndo ? sf::Color(255, 225, 50) : sf::Color(70, 100, 130, 200));
        uBox.setOutlineThickness(1.5f);
        window.draw(uBox);

        sf::Text uText;
        uText.setFont(font);
        uText.setString("UNDO");
        uText.setCharacterSize(17);
        uText.setFillColor(hUndo ? sf::Color(255, 235, 80) : sf::Color(220, 235, 245));
        uText.setPosition(startX + 40.0f, curY + 9.0f);
        window.draw(uText);

        rects.redoBtn = sf::FloatRect(startX + halfW + 10.0f, curY, halfW, 38.0f);
        bool hRedo = rects.redoBtn.contains(mouseX, mouseY);
        sf::RectangleShape rBox(sf::Vector2f(halfW, 38.0f));
        rBox.setPosition(startX + halfW + 10.0f, curY);
        rBox.setFillColor(hRedo ? sf::Color(45, 65, 85, 230) : sf::Color(25, 35, 48, 210));
        rBox.setOutlineColor(hRedo ? sf::Color(255, 225, 50) : sf::Color(70, 100, 130, 200));
        rBox.setOutlineThickness(1.5f);
        window.draw(rBox);

        sf::Text rText;
        rText.setFont(font);
        rText.setString("REDO");
        rText.setCharacterSize(17);
        rText.setFillColor(hRedo ? sf::Color(255, 235, 80) : sf::Color(220, 235, 245));
        rText.setPosition(startX + halfW + 50.0f, curY + 9.0f);
        window.draw(rText);
        curY += 56.0f;

        // 3. Save Section Card
        sf::RectangleShape saveCard(sf::Vector2f(panelW, 170.0f));
        saveCard.setPosition(startX, curY);
        saveCard.setFillColor(sf::Color(15, 22, 30, 230));
        saveCard.setOutlineColor(sf::Color(80, 130, 180, 220));
        saveCard.setOutlineThickness(2.0f);
        window.draw(saveCard);

        sf::Text sHeader;
        sHeader.setFont(font);
        sHeader.setString("SAVE IMAGE");
        sHeader.setCharacterSize(20);
        sHeader.setFillColor(sf::Color(255, 228, 50));
        sHeader.setPosition(startX + 14.0f, curY + 12.0f);
        window.draw(sHeader);

        sf::Text pLabel;
        pLabel.setFont(font);
        pLabel.setString("Mention Path :");
        pLabel.setCharacterSize(16);
        pLabel.setFillColor(sf::Color(200, 220, 240));
        pLabel.setPosition(startX + 14.0f, curY + 42.0f);
        window.draw(pLabel);

        // Path input box
        rects.savePathBox = sf::FloatRect(startX + 14.0f, curY + 68.0f, panelW - 28.0f, 36.0f);
        sf::RectangleShape pBox(sf::Vector2f(panelW - 28.0f, 36.0f));
        pBox.setPosition(startX + 14.0f, curY + 68.0f);
        pBox.setFillColor(sf::Color(25, 35, 48, 220));
        pBox.setOutlineColor(isTypingSave ? sf::Color(255, 225, 50) : sf::Color(70, 100, 130, 180));
        pBox.setOutlineThickness(isTypingSave ? 2.0f : 1.0f);
        window.draw(pBox);

        sf::Text pVal;
        pVal.setFont(font);
        pVal.setString(savePath + (isTypingSave ? "_" : ""));
        pVal.setCharacterSize(16);
        pVal.setFillColor(sf::Color(255, 255, 255));
        pVal.setPosition(startX + 20.0f, curY + 76.0f);
        window.draw(pVal);

        // Save Action Button
        rects.saveBtn = sf::FloatRect(startX + 14.0f, curY + 116.0f, panelW - 28.0f, 40.0f);
        bool hSave = rects.saveBtn.contains(mouseX, mouseY);
        sf::RectangleShape sBtn(sf::Vector2f(panelW - 28.0f, 40.0f));
        sBtn.setPosition(startX + 14.0f, curY + 116.0f);
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
        sBtnText.setPosition(startX + panelW / 2.0f, curY + 136.0f);
        window.draw(sBtnText);
    }

}
