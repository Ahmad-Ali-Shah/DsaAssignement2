#pragma once
#include <SFML/Graphics.hpp>

namespace GraphicsWindow {
    sf::RenderWindow* initWindow(unsigned int width, unsigned int height, const char* title) {

        sf::ContextSettings settings;

        settings.antialiasingLevel = 2;

        sf::RenderWindow* win = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close, settings);

        win->setFramerateLimit(60);
        
        return win;
    }
}
