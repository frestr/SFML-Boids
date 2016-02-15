#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "boid.h"
#include "inputhandler.h"

class BoidManager
{
public:
    BoidManager(int boidsAmount, sf::View windowView);

    void updatePositions(InputHandler& input, sf::View windowView);
    void drawBoids(sf::RenderWindow& window, bool drawArrows = false);

private:
    void addBoid(int xPos, int yPos, bool predator=false);
    void updateBoundingBox(Boid& boid);

    std::vector<Boid> boids;
    Boid::boidRefVec nearbyBoids;
    sf::Clock dtClock;
    sf::View view;
};
