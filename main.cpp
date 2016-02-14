#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include "boidmanager.h"
#include "inputhandler.h"

int getBoidsNum(char* argv[])
{
    int boidsNum;
    try
    {
        boidsNum = std::stoi(std::string(argv[1]));
    }
    catch (const std::exception& ex)
    {
        boidsNum = 20;
    }
    return boidsNum;
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Boids");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("DroidSans.ttf"))
            return 0;

    sf::Text fpsCounter;
    fpsCounter.setFont(font);
    fpsCounter.setPosition(10, 0);
    sf::Clock dtClock;
    sf::Clock fpsTimer;

    BoidManager boids(getBoidsNum(argv), window.getSize());
    InputHandler input;    

    while (window.isOpen())
    {
        input.readInput(window);
        if (input.shouldCloseWindow())
            window.close();

        double dt = dtClock.restart().asSeconds();
        if (fpsTimer.getElapsedTime().asMilliseconds() > 100)
        {
                fpsTimer.restart();
                int fps = (1.0 / dt > 60) ? 60 : (1.0 / dt);
                fpsCounter.setString("fps: " + std::to_string(fps));
        }

        boids.updatePositions(input);

        window.clear(sf::Color(200, 200, 200));
        boids.drawBoids(window, input.isKeyActive(sf::Keyboard::A));
        window.draw(fpsCounter);
        window.display();
    }

    return 0;
}
