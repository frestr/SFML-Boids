#include "inputhandler.h"
#include <algorithm>
#include <iostream>
#include <SFML/Config.hpp>

InputHandler::InputHandler() : closeWindow(false),
                               clickPos(Vector2(-1, -1)),
                               leftClick(false) {}

void InputHandler::readInput(sf::RenderWindow& window)
{
    clickPos = Vector2(-1, -1);
    scrollDelta = 0;
    sf::Event event;
    sf::Vector2f worldPos;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                closeWindow = true;
                break;
            case sf::Event::KeyPressed:
                if (isKeyActive(event.key.code))
                    activeKeys.erase(std::remove(activeKeys.begin(), activeKeys.end(), event.key.code), 
                            activeKeys.end());
                else
                    activeKeys.push_back(event.key.code);
                break;
            case sf::Event::MouseButtonPressed:
                worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                clickPos = Vector2(worldPos.x, worldPos.y);
                leftClick = event.mouseButton.button == sf::Mouse::Left;
                break;
#if SFML_VERSION_MINOR<3
            case sf::Event::MouseWheelMoved:
                scrollDelta = event.mouseWheel.delta;
                break;
#else
            case sf::Event::MouseWheelScrolled:
                scrollDelta = event.mouseWheelScroll.delta;
                break;
#endif
            default:
                break;
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

bool InputHandler::mouseClicked(char button)
{
    bool correctButton = true;
    if (button == 'l' || button == 'r')
        correctButton = (button == 'l' ? leftClick : !leftClick);

    return clickPos.getX() != -1 && clickPos.getY() != -1 && correctButton;
}

Vector2 InputHandler::getClickPos()
{
    return clickPos;
}

int InputHandler::mouseScrolled()
{
    return scrollDelta;
}
