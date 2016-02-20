#pragma once

#include <SFML/Graphics.hpp>

class UIManager
{
public:
    UIManager(sf::View originalView);
    
    void setFps(int fps);
    void setBoidCount(int boidCount);

    void drawUI(sf::RenderWindow& window);

private:
    sf::View view;

    sf::Font font;
    sf::Text fpsText;
    sf::Text boidCountText;
};
