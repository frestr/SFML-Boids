#include <random>
#include <memory>
#include "boidmanager.h"

BoidManager::BoidManager(int boidsAmount, sf::View windowView)
{
    view = windowView;

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> disX(0, view.getSize().x);
    std::uniform_int_distribution<> disY(0, view.getSize().y);

    for (int i = 0; i < boidsAmount; ++i)
        addBoid(disX(gen), disY(gen));

    dtClock.restart();
}

void BoidManager::updatePositions(InputHandler& input, sf::View windowView)
{
    if (windowView.getSize() != view.getSize())
    {
        view = windowView;
        for (Boid& boid : boids)
            updateBoundingBox(boid);
    }

    if (input.mouseClicked())
    {
        bool predator = input.mouseClicked('r');
        Vector2 clickPos = input.getClickPos();
        addBoid(clickPos.getX(), clickPos.getY(), predator);
    }

    bool scatter = input.isKeyActive(sf::Keyboard::S);
    int visionRadius = 250;
    for (Boid& boid : boids)
    {
        /* visionRadius = boid.isPredator() ? 500 : 250; */
        nearbyBoids.clear();
        for (Boid& compBoid : boids)
            if ((boid.getPosition() - compBoid.getPosition()).length() < visionRadius
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

void BoidManager::addBoid(int xPos, int yPos, bool predator)
{
    Boid boid(xPos, yPos, predator);
    updateBoundingBox(boid);
    boids.push_back(boid);
}

void BoidManager::updateBoundingBox(Boid& boid)
{
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    boid.setBoundingBox(Vector2(viewCenter.x - viewSize.x/2 + 100, viewCenter.y - viewSize.y/2 + 50), 
                        Vector2(viewCenter.x + viewSize.x/2 + 100, viewCenter.y + viewSize.y/2 - 50));
}
