#include "inputhandler.h"
#include <algorithm>

InputHandler::InputHandler() : closeWindow(false)
{

}

void InputHandler::readInput(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            closeWindow = true;
        if ((event.type == sf::Event::KeyReleased))
        {
            if (isKeyActive(event.key.code))
                activeKeys.erase(std::remove(activeKeys.begin(), activeKeys.end(), event.key.code), 
                        activeKeys.end());
            else
                activeKeys.push_back(event.key.code);
        }
    }
}

bool InputHandler::isKeyActive(sf::Keyboard::Key key)
{
    // Returns true if key is found in activeKeys
    return std::find(activeKeys.begin(), activeKeys.end(), key) != activeKeys.end();
}

bool InputHandler::shouldCloseWindow()
{
    return closeWindow;
}
