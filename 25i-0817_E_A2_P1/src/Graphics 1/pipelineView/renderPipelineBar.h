#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../../pipeline/pipeline.h"
#include "renderJobCard.h"
#include "../theme/drawBox.h"
#include "../theme/drawText.h"

namespace GraphicsPipeline {
    void renderPipelineBar(sf::RenderWindow& win, const sf::Font& font, float barX, float barY, float barW, float barH, ProcessingPipeline& pipeline) {
        GraphicsTheme::drawBox(win, barX, barY, barW, barH, sf::Color(15, 18, 24), sf::Color(35, 42, 55), 1.0f);
        std::string header = "CIRCULAR PROCESSING PIPELINE [FIFO QUEUE] - Size: " + std::to_string(pipeline.size()) + " / " + std::to_string(pipeline.capacity());
        GraphicsTheme::drawText(win, font, header, barX + 12.0f, barY + 8.0f, 13, sf::Color(255, 204, 0));

        Job jobs[32];
        int count = pipeline.getPendingJobs(jobs, 32);

        if (count == 0) {
            GraphicsTheme::drawText(win, font, "Queue is empty. Enqueue jobs from sidebar.", barX + 24.0f, barY + 36.0f, 13, sf::Color(120, 135, 150));
            return;
        }

        float cardX = barX + 12.0f;
        float cardY = barY + 30.0f;
        float cardW = 150.0f;
        float cardH = 34.0f;

        for (int i = 0; i < count && i < 6; i++) {
            renderJobCard(win, font, cardX, cardY, cardW, cardH, jobs[i].id, jobs[i].name, i == 0);
            cardX += cardW + 10.0f;
        }
    }
}
