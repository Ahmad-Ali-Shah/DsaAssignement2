#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace HomePage {

    void renderHomeTitle(sf::RenderTarget& target, const sf::Font& titleFont, const sf::Font& sigFont, float winW, float winH) {
        sf::Text title;
        title.setFont(titleFont);
        title.setString("DSA Assignment 2");
        title.setCharacterSize(38);
        title.setStyle(sf::Text::Bold);
        title.setFillColor(sf::Color::White);
        sf::FloatRect tb = title.getLocalBounds();
        title.setPosition((winW - tb.width) / 2.0f, winH * 0.44f);

        sf::Text subTitle;
        subTitle.setFont(titleFont);
        subTitle.setString("Image lab");
        subTitle.setCharacterSize(28);
        subTitle.setStyle(sf::Text::Bold);
        subTitle.setFillColor(sf::Color(220, 220, 225));
        sf::FloatRect sb = subTitle.getLocalBounds();
        subTitle.setPosition((winW - sb.width) / 2.0f, winH * 0.44f + 60.0f);

        sf::Text signature;
        signature.setFont(sigFont);
        signature.setString("Made by Ahmad i250817");
        signature.setCharacterSize(32);
        signature.setFillColor(sf::Color(180, 205, 240));
        sf::FloatRect sigb = signature.getLocalBounds();
        signature.setPosition((winW - sigb.width) / 2.0f, winH * 0.44f + 125.0f);

        target.draw(title);
        target.draw(subTitle);
        target.draw(signature);
    }

}
