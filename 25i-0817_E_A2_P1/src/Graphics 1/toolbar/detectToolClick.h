#pragma once
#include "../types/toolConstants.h"

namespace GraphicsToolbar {
    int detectToolClick(float barX, float barY, float barW, int mouseX, int mouseY) {
        float btnX = barX + 10.0f;
        float btnW = barW - 20.0f;
        float btnH = 26.0f;
        float curY = barY + 40.0f + 18.0f;

        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::LOAD; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::CROP; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::ROTATE_90; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::FLIP_H; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::BRIGHTNESS_UP; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::GRAYSCALE; } curY += 36.0f;

        curY += 18.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW/2 - 2 && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::UNDO; }
        if (mouseX >= btnX + btnW/2 + 2 && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::REDO; }
        curY += 36.0f;

        curY += 18.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::ENQUEUE_RESIZE; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::ENQUEUE_BLUR; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::ENQUEUE_BUCKET_STACK; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::ENQUEUE_BUCKET_QUEUE; } curY += 36.0f;

        curY += 18.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::PROCESS_NEXT; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::PROCESS_ALL; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::CLEAR_PIPELINE; } curY += 36.0f;

        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::TOGGLE_INSPECTOR; }

        return GraphicsTool::NONE;
    }
}
