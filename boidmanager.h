#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "boid.h"
#include "inputhandler.h"

class BoidManager
{
public:
    BoidManager(int boidsAmount, sf::Vector2u windowSize);

    void updatePositions(InputHandler& input);
    void drawBoids(sf::RenderWindow& window, bool drawArrows = false);

private:
    void addBoid(int xPos, int yPos);

    std::vector<Boid> boids;
    Boid::boidRefVec nearbyBoids;
    sf::Clock dtClock;
    sf::Vector2u windowSize;
};
