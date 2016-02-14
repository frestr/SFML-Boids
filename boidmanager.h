#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "boid.h"

class BoidManager
{
public:
    BoidManager(int boidsAmount, sf::Vector2u windowSize);

    void updatePositions(bool scatter=false);
    void drawBoids(sf::RenderWindow& window, bool drawArrows = false);

private:
    std::vector<Boid> boids;
    std::vector<std::reference_wrapper<Boid>> nearbyBoids;
    sf::Clock dtClock;
    std::map<char, bool> keys;
};
