#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace EditorPage {

    void renderEditorBanner(sf::RenderWindow& window, const sf::Texture& bannerTex, const sf::Font& font, const std::string& currentOperation) {
        float winW = static_cast<float>(window.getSize().x);
        
        // Use natural aspect ratio of the banner sprite
        float bannerW = 480.0f;
        float bannerH = bannerW * (static_cast<float>(bannerTex.getSize().y) / bannerTex.getSize().x);
        float bannerX = (winW - bannerW) / 2.0f;
        float bannerY = 660.0f;

        // Draw the authentic banner ribbon directly with zero black rectangular backing
        sf::Sprite bSprite(bannerTex);
        bSprite.setScale(bannerW / bannerTex.getSize().x, bannerH / bannerTex.getSize().y);
        bSprite.setPosition(bannerX, bannerY);
        window.draw(bSprite);

        // Text rendered directly on top of the ribbon
        std::string label = (currentOperation.empty() || currentOperation == "None") ? "CURRENT IMAGE" : currentOperation;
        std::string runningText = "--- " + label + " ---";

        // Subtle dark shadow for crisp readability on the white ribbon
        sf::Text bTextShadow;
        bTextShadow.setFont(font);
        bTextShadow.setString(runningText);
        bTextShadow.setCharacterSize(22);
        bTextShadow.setFillColor(sf::Color(180, 160, 140, 200));
        sf::FloatRect sb = bTextShadow.getLocalBounds();
        bTextShadow.setOrigin(sb.left + sb.width / 2.0f, sb.top + sb.height / 2.0f);
        bTextShadow.setPosition(winW / 2.0f + 1.5f, bannerY + bannerH * 0.44f + 1.5f);
        window.draw(bTextShadow);

        sf::Text bText;
        bText.setFont(font);
        bText.setString(runningText);
        bText.setCharacterSize(22);
        bText.setFillColor(sf::Color(25, 25, 30));
        sf::FloatRect tb = bText.getLocalBounds();
        bText.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
        bText.setPosition(winW / 2.0f, bannerY + bannerH * 0.44f);
        window.draw(bText);
    }

}
