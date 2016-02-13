#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
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
            return 0;

    sf::Text fpsCounter;
    fpsCounter.setFont(font);
    fpsCounter.setPosition(10, 0);
    sf::Clock dtClock;
    sf::Clock fpsTimer;

    BoidManager boids(getBoidsNum(argv), window.getSize());

    std::map<char, bool> keyStates = {{'a', false}, {'s', false}};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyReleased))
                switch (event.key.code)
                {
                    case sf::Keyboard::A:
                        keyStates.at('a') = ! keyStates.at('a');
                        break;
                    case sf::Keyboard::S:
                        keyStates.at('s') = ! keyStates.at('s');
                        break;
                    default:
                        break;
                }
        }
        /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) */
        /*         window.close(); */
        double dt = dtClock.restart().asSeconds();
        if (fpsTimer.getElapsedTime().asMilliseconds() > 100)
        {
                fpsTimer.restart();
                int fps = (1.0 / dt > 60) ? 60 : (1.0 / dt);
                fpsCounter.setString("fps: " + std::to_string(fps));
        }

        boids.updatePositions(keyStates.at('s'));

        window.clear(sf::Color(200, 200, 200));
        boids.drawBoids(window, keyStates.at('a'));
        window.draw(fpsCounter);
        window.display();
    }

    return 0;
}
