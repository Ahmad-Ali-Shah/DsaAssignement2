#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../toolbar/renderToolPanel.h"
#include "../canvas/renderCanvas.h"
#include "../pipelineView/renderPipelineBar.h"
#include "../inspectorView/renderInspectorHUD.h"
#include "../animator/renderDataStructureAnimation.h"
#include "../../image.h"
#include "../../history/history.h"
#include "../../pipeline/pipeline.h"

namespace GraphicsApp {
    void renderApp(sf::RenderWindow& win, const sf::Font& font, const sf::Font& sigFont, const sf::Texture& canvasTex, const sf::Texture& spriteTex, int mouseX, int mouseY, HistoryManager& history, ProcessingPipeline& pipeline, bool showInspector, const std::string& lastAction) {
        win.clear(sf::Color(12, 14, 18));

       
        GraphicsToolbar::renderToolPanel(win, font, 0.0f, 0.0f, 240.0f, 800.0f, mouseX, mouseY, history.getUndoSize(), history.getRedoSize());

       
        GraphicsTheme::drawText(win, sigFont, "Made by Ahmad", 25.0f, 765.0f, 18, sf::Color(255, 204, 0));

    
        GraphicsCanvas::renderCanvas(win, canvasTex, 245.0f, 10.0f, 750.0f, 640.0f);

       
        GraphicsPipeline::renderPipelineBar(win, font, 245.0f, 655.0f, 1025.0f, 135.0f, pipeline);

        
        GraphicsAnimator::renderDataStructureAnimation(win, font, spriteTex, 1000.0f, 10.0f, 270.0f, 200.0f, history.getUndoSize(), pipeline.size(), lastAction);

      
        if (showInspector) {
            GraphicsInspector::renderInspectorHUD(win, font, 400.0f, 120.0f, 480.0f, 380.0f, history, pipeline);
        }

        win.display();
    }
}
