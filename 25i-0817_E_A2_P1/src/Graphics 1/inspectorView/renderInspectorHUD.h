#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"
#include "../theme/drawBox.h"
#include "../theme/drawText.h"

namespace GraphicsInspector {
    void renderInspectorHUD(sf::RenderWindow& win, const sf::Font& font, float panelX, float panelY, float panelW, float panelH, HistoryManager& history, ProcessingPipeline& pipeline) {
        GraphicsTheme::drawBox(win, panelX, panelY, panelW, panelH, sf::Color(15, 20, 30, 240), sf::Color(0, 204, 255), 2.0f);
        GraphicsTheme::drawText(win, font, "DATA STRUCTURE INSPECTOR (SECTION 6.7)", panelX + 14.0f, panelY + 12.0f, 15, sf::Color(0, 255, 255));

        float textY = panelY + 40.0f;
        GraphicsTheme::drawText(win, font, "[STACK TELEMETRY - Malik stackType]", panelX + 14.0f, textY, 13, sf::Color(255, 204, 0)); textY += 20.0f;
        GraphicsTheme::drawText(win, font, "Undo Stack Size: " + std::to_string(history.getUndoSize()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 18.0f;
        GraphicsTheme::drawText(win, font, "Redo Stack Size: " + std::to_string(history.getRedoSize()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 18.0f;
        GraphicsTheme::drawText(win, font, "Total Stack Pushes: " + std::to_string(history.getPushCount()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 18.0f;
        GraphicsTheme::drawText(win, font, "Total Stack Pops:   " + std::to_string(history.getPopCount()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 26.0f;

        GraphicsTheme::drawText(win, font, "[QUEUE TELEMETRY - Malik circular queueType]", panelX + 14.0f, textY, 13, sf::Color(255, 204, 0)); textY += 20.0f;
        GraphicsTheme::drawText(win, font, "Current Queue Size: " + std::to_string(pipeline.size()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 18.0f;
        GraphicsTheme::drawText(win, font, "Queue Capacity:     " + std::to_string(pipeline.capacity()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 18.0f;
        GraphicsTheme::drawText(win, font, "Max Recorded Size:  " + std::to_string(pipeline.getMaxRecordedQueueSize()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 18.0f;
        GraphicsTheme::drawText(win, font, "Total addQueue():   " + std::to_string(pipeline.getAddCount()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 18.0f;
        GraphicsTheme::drawText(win, font, "Total deleteQueue():" + std::to_string(pipeline.getDeleteCount()), panelX + 24.0f, textY, 12, sf::Color(220, 220, 220)); textY += 26.0f;

        GraphicsTheme::drawText(win, font, "Click 'Toggle Inspector HUD' to close.", panelX + 14.0f, textY, 11, sf::Color(140, 160, 180));
    }
}
