#pragma once
#include "homeConstants.h"

namespace HomePage {

    void updateCatState(int& stage, int& frameIdx, float& timer, float& catX, float dt, float winW, int& sitLoops, bool& reachedEnd) {
        timer += dt;

        if (stage == HomeConstants::STAGE_SITTING) {
            float frameDuration = 0.18f;
            if (timer >= frameDuration) {
                timer -= frameDuration;
                frameIdx++;
                if (frameIdx >= HomeConstants::SITTING_FRAMES) {
                    frameIdx = 0;
                    sitLoops++;
                    if (sitLoops >= 2) {
                        stage = HomeConstants::STAGE_STANDING;
                        frameIdx = 0;
                        timer = 0.0f;
                    }
                }
            }
        }
        else if (stage == HomeConstants::STAGE_STANDING) {
            float frameDuration = 0.24f;
            if (timer >= frameDuration) {
                timer -= frameDuration;
                frameIdx++;
                if (frameIdx >= HomeConstants::STANDING_FRAMES) {
                    stage = HomeConstants::STAGE_WALKING;
                    frameIdx = 0;
                    timer = 0.0f;
                }
            }
        }
        else if (stage == HomeConstants::STAGE_WALKING) {
            float frameDuration = 0.14f;
            catX += 75.0f * dt;
            if (timer >= frameDuration) {
                timer -= frameDuration;
                frameIdx = (frameIdx + 1) % HomeConstants::WALKING_FRAMES;
            }
            if (catX >= 300.0f) {
                stage = HomeConstants::STAGE_RUNNING;
                frameIdx = 0;
                timer = 0.0f;
            }
        }
        else if (stage == HomeConstants::STAGE_RUNNING) {
            float frameDuration = 0.085f;
            catX += 260.0f * dt;
            if (timer >= frameDuration) {
                timer -= frameDuration;
                frameIdx = (frameIdx + 1) % HomeConstants::RUNNING_FRAMES;
            }
            if (catX >= winW + 40.0f) {
                reachedEnd = true;
            }
        }
    }

}
