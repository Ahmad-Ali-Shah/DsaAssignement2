#pragma once
#include <SFML/Graphics.hpp>

namespace GraphicsCanvas {
    bool getCanvasPixelCoords(int mouseX, int mouseY, int imgW, int imgH, float viewX, float viewY, float viewW, float viewH, int& outX, int& outY) {
        if (imgW <= 0 || imgH <= 0) 
        return false;

        float scaleX = (viewW - 20.0f) / imgW;

        float scaleY = (viewH - 20.0f) / imgH;

        float scale = scaleX < scaleY ? scaleX : scaleY;

        if (scale > 1.0f) 
        scale = 1.0f;


        float drawW = imgW * scale;

        float drawH = imgH * scale;

        float posX = viewX + (viewW - drawW) / 2.0f;

        float posY = viewY + (viewH - drawH) / 2.0f;


        if (mouseX >= posX && mouseX < posX + drawW && mouseY >= posY && mouseY < posY + drawH) {

            outX = static_cast<int>((mouseX - posX) / scale);

            outY = static_cast<int>((mouseY - posY) / scale);

            if (outX >= imgW)
             outX = imgW - 1;
            if (outY >= imgH) 
            outY = imgH - 1;

            return true;

        }
        
        return false;
    }
}
