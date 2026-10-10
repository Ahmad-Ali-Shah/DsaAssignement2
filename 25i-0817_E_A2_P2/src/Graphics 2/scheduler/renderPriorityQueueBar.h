#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../../pipeline/pipeline.h"
#include "renderPriorityCard.h"
#include "renderBarrierIndicator.h"

namespace GraphicsScheduler {
    void renderPriorityQueueBar(sf::RenderWindow& win, const sf::Font& font, float barX, float barY, float barW, float barH, ProcessingPipeline& pipeline) {
        sf::RectangleShape bg(sf::Vector2f(barW, barH));
        bg.setPosition(barX, barY);
        bg.setFillColor(sf::Color(15, 18, 24));
        bg.setOutlineColor(sf::Color(35, 42, 55));
        bg.setOutlineThickness(1.0f);
        win.draw(bg);

        std::string modeStr = (pipeline.getMode() == SchedulerMode::FIFO) ? "FIFO (Phase 1)" : "PRIORITY SCHEDULER (Phase 2)";
        sf::Text header;
        header.setFont(font);
        header.setString("ACTIVE SCHEDULER: " + modeStr + " | Pending: " + std::to_string(pipeline.getCurrentQueueSize()));
        header.setCharacterSize(13);
        header.setFillColor(sf::Color(255, 204, 0));
        header.setPosition(barX + 12.0f, barY + 8.0f);
        win.draw(header);

        if (pipeline.isEmpty()) {
            sf::Text emptyMsg;
            emptyMsg.setFont(font);
            emptyMsg.setString("Scheduler is idle. Submit jobs from sidebar.");
            emptyMsg.setCharacterSize(13);
            emptyMsg.setFillColor(sf::Color(120, 135, 150));
            emptyMsg.setPosition(barX + 24.0f, barY + 36.0f);
            win.draw(emptyMsg);
            return;
        }

        float cardX = barX + 12.0f;
        float cardY = barY + 30.0f;
        float cardW = 150.0f;
        float cardH = 42.0f;

        // Display next job to be served
        Job topJob = pipeline.peekNextJob();
        renderPriorityCard(win, font, cardX, cardY, cardW, cardH, topJob.id, topJob.name, topJob.priority, topJob.isBarrier());
        cardX += cardW + 10.0f;

        renderBarrierIndicator(win, cardX, cardY, cardH);
        cardX += 10.0f;

        sf::Text remaining;
        remaining.setFont(font);
        remaining.setString("+ " + std::to_string(pipeline.getCurrentQueueSize() - 1) + " jobs awaiting dispatch");
        remaining.setCharacterSize(12);
        remaining.setFillColor(sf::Color(160, 180, 200));
        remaining.setPosition(cardX, cardY + 12.0f);
        win.draw(remaining);
    }
}
