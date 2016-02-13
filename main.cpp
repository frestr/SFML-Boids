#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "boidmanager.h"

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
    {
            return 0;
    }

    sf::Text fpsCounter;
    fpsCounter.setFont(font);
    fpsCounter.setPosition(10, 0);
    sf::Clock dtClock;
    sf::Clock fpsTimer;

    BoidManager boids(getBoidsNum(argv), window.getSize());

    bool drawArrows = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::A))
                drawArrows = ! drawArrows;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        double dt = dtClock.restart().asSeconds();
        if (fpsTimer.getElapsedTime().asMilliseconds() > 100)
        {
                fpsTimer.restart();
                int fps = (1.0 / dt > 60) ? 60 : (1.0 / dt);
                fpsCounter.setString("fps: " + std::to_string(fps));
        }

        boids.updatePositions();

        window.clear(sf::Color(200, 200, 200));
        boids.drawBoids(window, drawArrows);
        window.draw(fpsCounter);
        window.display();
    }

    return 0;
}
