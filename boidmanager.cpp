#include <random>
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
        boid.setBoundingBox(Vector2(0, 0), Vector2(windowSize.x, windowSize.y));

    dtClock.restart();
}

void BoidManager::updatePositions()
{
    /* double dt = clock.restart().asSeconds(); */
    for (Boid& boid : boids)
    {
        // This is a temporary solution
        // Also, remember to not include the boid itself
        // (in the non-temporary solution)
        std::vector<Boid>* nearbyBoids = &boids;

        boid.updateVelocity(*nearbyBoids);
    }

    // All boids should update their velocities before they update their
    // positions. This way, no boids get a "head start".
    double dt = dtClock.restart().asSeconds();
    for (Boid& boid : boids)
        boid.updatePosition(dt);
}

void BoidManager::drawBoids(sf::RenderWindow& window)
{
    for (Boid& boid : boids)
        boid.draw(window);
}
