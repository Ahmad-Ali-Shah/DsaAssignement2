#pragma once
#include <cmath>

namespace SelectionPage {

    void updateShipSpeed(float mouseX, float mouseY, float prevX, float prevY, float dt, float speedThreshold, bool& outIsFast) {
        if (dt <= 0.0001f) {
            outIsFast = false;
            return;
        }

        float dx = mouseX - prevX;
        float dy = mouseY - prevY;
        float dist = std::sqrt(dx * dx + dy * dy);
        float speed = dist / dt;

        outIsFast = (speed >= speedThreshold);
    }

}
