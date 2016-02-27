#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include "boid.h"
#include "inputhandler.h"

class Boid;

class BoidManager
{
public:
    BoidManager(int boidsAmount, sf::View windowView);
    ~BoidManager();

    void updatePositions(InputHandler& input, sf::View windowView);
    void drawBoids(sf::RenderWindow& window, bool drawArrows = false);
    int getBoidCount();

private:
    void addBoid(int xPos, int yPos, bool predator=false);
    void updateBoundingBox(Boid& boid);
    void batchUpdatePositions(int offset, int batchSize, bool scatter);

    std::vector<Boid> boids;
    sf::Clock dtClock;
    sf::View view;

    int threadNum;
    std::vector<std::thread> threads;
};
