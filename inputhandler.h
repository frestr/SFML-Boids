#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class InputHandler
{
public:
    InputHandler();

    void readInput(sf::RenderWindow& window);
    bool isKeyActive(sf::Keyboard::Key key);
    bool shouldCloseWindow();

private:
    std::vector<sf::Keyboard::Key> activeKeys; // i.e. toggled keys
    bool closeWindow;
};
