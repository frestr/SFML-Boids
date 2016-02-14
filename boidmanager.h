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
    std::vector<Boid> boids;
    Boid::boidRefVec nearbyBoids;
    sf::Clock dtClock;
    std::map<char, bool> keys;
};
