#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "boidmanager.h"
#include "inputhandler.h"
#include "uimanager.h"

int getBoidsNum(char* argv[])
{
    int boidsNum;
    try
    {
        boidsNum = std::stoi(std::string(argv[1]));
    }
    catch (const std::exception& ex)
    {
        boidsNum = 50;
    }
    return boidsNum;
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Boids");
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    sf::View originalView = view;

    sf::Clock dtClock;
    sf::Clock fpsTimer;

    BoidManager boids(getBoidsNum(argv), view);
    InputHandler input;    
    UIManager ui(window.getView());

    while (window.isOpen())
    {
        input.readInput(window);
        if (input.shouldCloseWindow())
        {
            window.close();
            break;
        }

        int scrollDelta = input.mouseScrolled();
        if (scrollDelta > 0 && view.getSize().y > 200)
            view.zoom(0.75);
        else if (scrollDelta < 0 && view.getSize().y < 4000)
            view.zoom(1.0/0.75);
        window.setView(view);

        double dt = dtClock.restart().asSeconds();
        if (fpsTimer.getElapsedTime().asMilliseconds() > 100)
        {
            fpsTimer.restart();
            int fps = (1.0 / dt > 60) ? 60 : (1.0 / dt);
            ui.setFps(fps);
        }

        boids.updatePositions(input, view);
        ui.setBoidCount(boids.getBoidCount());

        window.clear(sf::Color(200, 200, 200));
        boids.drawBoids(window, input.isKeyActive(sf::Keyboard::A));
        ui.drawUI(window);

        window.display();
    }

    return 0;
}
