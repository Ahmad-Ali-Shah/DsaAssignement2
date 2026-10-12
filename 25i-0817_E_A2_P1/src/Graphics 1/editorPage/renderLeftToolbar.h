#pragma once
#include <SFML/Graphics.hpp>
#include "editorConstants.h"
#include "loadEditorAssets.h"

namespace EditorPage {

    struct LeftButtonRects {
        sf::FloatRect loadBtn;
        sf::FloatRect cropBtn;
        sf::FloatRect rot90Btn;
        sf::FloatRect rot180Btn;
        sf::FloatRect rot270Btn;
        sf::FloatRect rot360Btn;
        sf::FloatRect flipHBtn;
        sf::FloatRect flipVBtn;
        sf::FloatRect grayBtn;
        sf::FloatRect brightBtn;
        sf::FloatRect blurBtn;
        sf::FloatRect bucketBtn;
        sf::FloatRect resizeBtn;
    };

    void renderLeftToolbar(sf::RenderWindow& window, const EditorTextures& tex, const sf::Font& font, float mouseX, float mouseY, LeftButtonRects& rects) {
        float startX = 24.0f;
        float curY = 30.0f;

        // Section Title: OPERATIONS
        sf::Text title;
        title.setFont(font);
        title.setString("OPERATIONS");
        title.setCharacterSize(22);
        title.setFillColor(sf::Color(255, 228, 50));
        title.setPosition(startX, curY);
        window.draw(title);
        curY += 32.0f;

        // Helper to draw an icon button
        auto drawButton = [&](sf::FloatRect& btnRect, const sf::Texture& t, sf::IntRect uv, const std::string& label, float scale, float yOffset = 0.0f) {
            float bw = 138.0f;
            float bh = 42.0f;
            btnRect = sf::FloatRect(startX, curY, bw, bh);

            bool hovered = btnRect.contains(mouseX, mouseY);
            sf::RectangleShape bg(sf::Vector2f(bw, bh));
            bg.setPosition(startX, curY);
            bg.setFillColor(hovered ? sf::Color(45, 65, 85, 230) : sf::Color(20, 28, 38, 200));
            bg.setOutlineColor(hovered ? sf::Color(255, 225, 50) : sf::Color(70, 95, 120, 180));
            bg.setOutlineThickness(hovered ? 2.0f : 1.0f);
            window.draw(bg);

            sf::Sprite icon(t);
            icon.setTextureRect(uv);
            icon.setScale(scale, scale);
            icon.setPosition(startX + 8.0f, curY + (bh - uv.height * scale) / 2.0f + yOffset);
            window.draw(icon);

            sf::Text txt;
            txt.setFont(font);
            txt.setString(label);
            txt.setCharacterSize(16);
            txt.setFillColor(hovered ? sf::Color(255, 235, 80) : sf::Color(220, 230, 240));
            txt.setPosition(startX + 52.0f, curY + 11.0f);
            window.draw(txt);

            curY += bh + 8.0f;
        };

        // 1) Load Image (compact camera icon separated cleanly from label)
        drawButton(rects.loadBtn, tex.imageLoad, sf::IntRect(143, 31, 232, 138), "Load", 0.16f);

        // 2) Crop
        drawButton(rects.cropBtn, tex.crop, sf::IntRect(0, 0, tex.crop.getSize().x, tex.crop.getSize().y), "Crop", 0.18f);

        // 3) Rotations: 90, 180, 270, 360
        drawButton(rects.rot90Btn, tex.rotations, sf::IntRect(EditorConstants::ROT_90_X, EditorConstants::ROT_90_Y, EditorConstants::ROT_90_W, EditorConstants::ROT_90_H), "Rot 90", 0.24f);
        drawButton(rects.rot180Btn, tex.rotations, sf::IntRect(EditorConstants::ROT_180_X, EditorConstants::ROT_180_Y, EditorConstants::ROT_180_W, EditorConstants::ROT_180_H), "Rot 180", 0.24f);
        drawButton(rects.rot270Btn, tex.rotations, sf::IntRect(EditorConstants::ROT_270_X, EditorConstants::ROT_270_Y, EditorConstants::ROT_270_W, EditorConstants::ROT_270_H), "Rot 270", 0.24f);
        drawButton(rects.rot360Btn, tex.rotations, sf::IntRect(EditorConstants::ROT_360_X, EditorConstants::ROT_360_Y, EditorConstants::ROT_360_W, EditorConstants::ROT_360_H), "Rot 360", 0.28f);

        // 4) Flip Horizontal and Vertical using arrow.png (Flip V shifted up slightly)
        drawButton(rects.flipHBtn, tex.arrow, sf::IntRect(0, 0, tex.arrow.getSize().x, tex.arrow.getSize().y), "Flip H", 0.18f);
        drawButton(rects.flipVBtn, tex.arrow, sf::IntRect(0, 0, tex.arrow.getSize().x, tex.arrow.getSize().y), "Flip V", 0.18f, -4.0f);

        // 5) Adjustment: Grayscale & Brightness
        drawButton(rects.grayBtn, tex.adjustment, sf::IntRect(EditorConstants::ADJ_GRAY_X, EditorConstants::ADJ_GRAY_Y, EditorConstants::ADJ_GRAY_W, EditorConstants::ADJ_GRAY_H), "Grayscale", 0.28f);
        drawButton(rects.brightBtn, tex.adjustment, sf::IntRect(EditorConstants::ADJ_BRIGHT_X, EditorConstants::ADJ_BRIGHT_Y, EditorConstants::ADJ_BRIGHT_W, EditorConstants::ADJ_BRIGHT_H), "Bright +", 0.28f);

        // 6) Tools: Blur, Bucket, Resize
        drawButton(rects.blurBtn, tex.tools, sf::IntRect(EditorConstants::TOOL_BLUR_X, EditorConstants::TOOL_BLUR_Y, EditorConstants::TOOL_BLUR_W, EditorConstants::TOOL_BLUR_H), "Blur", 0.20f);
        drawButton(rects.bucketBtn, tex.tools, sf::IntRect(EditorConstants::TOOL_BUCKET_X, EditorConstants::TOOL_BUCKET_Y, EditorConstants::TOOL_BUCKET_W, EditorConstants::TOOL_BUCKET_H), "Fill", 0.20f);
        drawButton(rects.resizeBtn, tex.tools, sf::IntRect(EditorConstants::TOOL_RESIZE_X, EditorConstants::TOOL_RESIZE_Y, EditorConstants::TOOL_RESIZE_W, EditorConstants::TOOL_RESIZE_H), "Half Size", 0.20f);
    }

}
