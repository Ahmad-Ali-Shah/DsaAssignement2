#pragma once
#include "../types/toolConstants.h"

namespace GraphicsToolbar {
    int detectToolClick(float barX, float barY, float barW, int mouseX, int mouseY) {
        float btnX = barX + 10.0f;
        float btnW = barW - 20.0f;
        float btnH = 26.0f;
        float curY = barY + 40.0f + 18.0f;

        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::load; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::crop; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::rotate90; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::flipH; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::brightnessUp; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::grayscale; } curY += 36.0f;

        curY += 18.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW/2 - 2 && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::undo; }
        if (mouseX >= btnX + btnW/2 + 2 && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::redo; }
        curY += 36.0f;

        curY += 18.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::enqueueResize; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::enqueueBlur; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::enqueueBucketStack; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::enqueueBucketQueue; } curY += 36.0f;

        curY += 18.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::processNext; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::processAll; } curY += 30.0f;
        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::clearPipeline; } curY += 36.0f;

        if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= curY && mouseY <= curY + btnH) { return GraphicsTool::toggleInspector; }

        return GraphicsTool::none;
    }
}
