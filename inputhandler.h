#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "vector2.h"

class InputHandler
{
public:
    InputHandler();

    void readInput(sf::RenderWindow& window);
    bool isKeyActive(sf::Keyboard::Key key);
    bool shouldCloseWindow();
    bool mouseClicked();
    Vector2 getClickPos();

private:
    std::vector<sf::Keyboard::Key> activeKeys; // i.e. toggled keys
    bool closeWindow;
    Vector2 clickPos;
};
