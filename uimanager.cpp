#include "uimanager.h"
#include <iostream>

UIManager::UIManager(sf::View originalView)
{
    if (!font.loadFromFile("DroidSans.ttf"))
    {
        std::cout << "In UIManager::UIManager(): Unable to load font DroidSans.ttf" << std::endl;
        return;
    }

    fpsText.setFont(font);
    fpsText.setCharacterSize(25);
    fpsText.setPosition(34, 5);
    
    boidCountText.setFont(font);
    boidCountText.setCharacterSize(25);
    boidCountText.setPosition(10, 40);

    view = originalView;
}

void UIManager::setFps(int fps)
{
    fpsText.setString("fps: " + std::to_string(fps));
}

void UIManager::setBoidCount(int boidCount)
{
    boidCountText.setString("boids: " + std::to_string(boidCount));
}

void UIManager::drawUI(sf::RenderWindow& window)
{
    sf::View currView = window.getView();

    window.setView(view);

    window.draw(fpsText);
    window.draw(boidCountText);

    window.setView(currView);
}
