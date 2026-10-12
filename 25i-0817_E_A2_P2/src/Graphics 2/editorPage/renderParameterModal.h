#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace EditorPage {

    struct ModalInputs {
        bool active;
        std::string title;
        std::string label1;
        std::string label2;
        std::string val1;
        std::string val2;
        int activeField; // 1 or 2
        int opType;
    };

    void renderParameterModal(sf::RenderWindow& window, const sf::Font& font, const sf::Font& titleFont, const ModalInputs& modal, sf::FloatRect& okBtnRect, sf::FloatRect& cancelBtnRect) {
        if (!modal.active) return;

        float winW = static_cast<float>(window.getSize().x);
        float winH = static_cast<float>(window.getSize().y);

        // Dark dim backdrop
        sf::RectangleShape dim(sf::Vector2f(winW, winH));
        dim.setFillColor(sf::Color(0, 0, 0, 190));
        window.draw(dim);

        // Modal Box
        float modalW = 460.0f;
        float modalH = 260.0f;
        float modalX = (winW - modalW) / 2.0f;
        float modalY = (winH - modalH) / 2.0f;

        sf::RectangleShape box(sf::Vector2f(modalW, modalH));
        box.setPosition(modalX, modalY);
        box.setFillColor(sf::Color(20, 28, 38, 245));
        box.setOutlineColor(sf::Color(255, 225, 50, 240));
        box.setOutlineThickness(2.5f);
        window.draw(box);

        // Title
        sf::Text t;
        t.setFont(titleFont);
        t.setString(modal.title);
        t.setCharacterSize(22);
        t.setFillColor(sf::Color(255, 228, 50));
        sf::FloatRect tb = t.getLocalBounds();
        t.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
        t.setPosition(winW / 2.0f, modalY + 36.0f);
        window.draw(t);

        // Field 1
        sf::Text l1;
        l1.setFont(font);
        l1.setString(modal.label1 + " : " + modal.val1 + (modal.activeField == 1 ? "_" : ""));
        l1.setCharacterSize(20);
        l1.setFillColor(modal.activeField == 1 ? sf::Color(255, 235, 80) : sf::Color(220, 230, 240));
        l1.setPosition(modalX + 40.0f, modalY + 80.0f);
        window.draw(l1);

        // Field 2 (if present)
        if (!modal.label2.empty()) {
            sf::Text l2;
            l2.setFont(font);
            l2.setString(modal.label2 + " : " + modal.val2 + (modal.activeField == 2 ? "_" : ""));
            l2.setCharacterSize(20);
            l2.setFillColor(modal.activeField == 2 ? sf::Color(255, 235, 80) : sf::Color(220, 230, 240));
            l2.setPosition(modalX + 40.0f, modalY + 124.0f);
            window.draw(l2);
        }

        // OK and Cancel Buttons
        okBtnRect = sf::FloatRect(modalX + 60.0f, modalY + modalH - 58.0f, 140.0f, 38.0f);
        sf::RectangleShape okBox(sf::Vector2f(140.0f, 38.0f));
        okBox.setPosition(okBtnRect.left, okBtnRect.top);
        okBox.setFillColor(sf::Color(35, 85, 50));
        okBox.setOutlineColor(sf::Color(100, 200, 120));
        okBox.setOutlineThickness(1.5f);
        window.draw(okBox);

        sf::Text okText;
        okText.setFont(font);
        okText.setString("APPLY (ENTER)");
        okText.setCharacterSize(16);
        okText.setFillColor(sf::Color::White);
        okText.setPosition(okBtnRect.left + 16.0f, okBtnRect.top + 9.0f);
        window.draw(okText);

        cancelBtnRect = sf::FloatRect(modalX + modalW - 200.0f, modalY + modalH - 58.0f, 140.0f, 38.0f);
        sf::RectangleShape cancelBox(sf::Vector2f(140.0f, 38.0f));
        cancelBox.setPosition(cancelBtnRect.left, cancelBtnRect.top);
        cancelBox.setFillColor(sf::Color(85, 35, 35));
        cancelBox.setOutlineColor(sf::Color(200, 100, 100));
        cancelBox.setOutlineThickness(1.5f);
        window.draw(cancelBox);

        sf::Text cancelText;
        cancelText.setFont(font);
        cancelText.setString("CANCEL (ESC)");
        cancelText.setCharacterSize(16);
        cancelText.setFillColor(sf::Color::White);
        cancelText.setPosition(cancelBtnRect.left + 18.0f, cancelBtnRect.top + 9.0f);
        window.draw(cancelText);
    }

}
