#include <SFML/Graphics.hpp>
#include <iostream>
#include "boidmanager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Boids");
    window.setFramerateLimit(60);

    BoidManager boids(20, window.getSize());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        boids.updatePositions();

        window.clear(sf::Color(200, 200, 200));
        boids.drawBoids(window);
        window.display();
    }

    return 0;
}
