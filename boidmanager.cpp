#include <random>
#include <memory>
#include "boidmanager.h"

BoidManager::BoidManager(int boidsAmount, sf::Vector2u windowSize)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> disX(0, windowSize.x);
    std::uniform_int_distribution<> disY(0, windowSize.y);

    for (int i = 0; i < boidsAmount; ++i)
        boids.push_back(Boid(disX(gen), disY(gen)));

    for (Boid& boid : boids)
        boid.setBoundingBox(Vector2(100, 50), Vector2(windowSize.x-100, windowSize.y-50));

    dtClock.restart();
}

void BoidManager::updatePositions(InputHandler& input)
{
    bool scatter = input.isKeyActive(sf::Keyboard::S);

    for (Boid& boid : boids)
    {
        nearbyBoids.clear();
        for (Boid& compBoid : boids)
            if ((boid.getPosition() - compBoid.getPosition()).length() < 250
                    && compBoid.getPosition() != boid.getPosition())
                nearbyBoids.push_back(compBoid);

        boid.updateVelocity(nearbyBoids, scatter);
    }

    // All boids should update their velocities before they update their
    // positions. This way, no boids get a "head start".
    double dt = dtClock.restart().asSeconds();
    for (Boid& boid : boids)
        boid.updatePosition(dt);
}

void BoidManager::drawBoids(sf::RenderWindow& window, bool drawArrows)
{
    for (Boid& boid : boids)
        boid.draw(window, drawArrows);
}
