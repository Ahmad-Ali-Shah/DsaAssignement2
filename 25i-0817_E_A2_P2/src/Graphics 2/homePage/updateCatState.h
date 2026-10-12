#pragma once
#include "homeConstants.h"

namespace HomePage {

    void updateCatState(int& stage, int& frameIdx, float& timer, float& catX, float dt, float winW, int& sitLoops, bool& reachedEnd) {
        timer += dt;

        if (stage == HomeConstants::STAGE_SITTING) {
            float frameDuration = 0.12f; // Snappier sit
            if (timer >= frameDuration) {
                timer -= frameDuration;
                frameIdx++;
                if (frameIdx >= HomeConstants::SITTING_FRAMES) {
                    frameIdx = 0;
                    sitLoops++;
                    if (sitLoops >= 1) { // 1 sit loop instead of 2 to start moving fast
                        stage = HomeConstants::STAGE_STANDING;
                        frameIdx = 0;
                        timer = 0.0f;
                    }
                }
            }
        }
        else if (stage == HomeConstants::STAGE_STANDING) {
            float frameDuration = 0.12f; // Quick stand
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
            float frameDuration = 0.09f;
            catX += 130.0f * dt; // Faster walk speed
            if (timer >= frameDuration) {
                timer -= frameDuration;
                frameIdx = (frameIdx + 1) % HomeConstants::WALKING_FRAMES;
            }
            if (catX >= 260.0f) {
                stage = HomeConstants::STAGE_RUNNING;
                frameIdx = 0;
                timer = 0.0f;
            }
        }
        else if (stage == HomeConstants::STAGE_RUNNING) {
            float frameDuration = 0.06f;
            catX += 450.0f * dt; // Fast sprint across screen
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
