#include <random>
#include <memory>
#include "boidmanager.h"

BoidManager::BoidManager(int boidsAmount, sf::View windowView)
{
    threadNum = std::thread::hardware_concurrency();
    if (threadNum == 0)
        threadNum = 1;

    threads = std::vector<std::thread>(threadNum);

    view = windowView;

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> disX(0, view.getSize().x);
    std::uniform_int_distribution<> disY(0, view.getSize().y);

    for (int i = 0; i < boidsAmount; ++i)
        addBoid(disX(gen), disY(gen));

    dtClock.restart();
}

BoidManager::~BoidManager()
{
    try
    {
        // Make sure all the threads are joined
        for (int i = 0; i < threadNum; ++i)
            threads.at(i).join();
    }
    catch (const std::exception& ex)
    {
        // I'm a naughty boy
        return;
    }
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

    int batchSize = boids.size() / threadNum;
    for (int i = 0; i < threadNum; ++i)
        threads.at(i) = std::thread(&BoidManager::batchUpdatePositions, this, i, batchSize, scatter);

    for (int i = 0; i < threadNum; ++i)
        threads.at(i).join();

    // All boids should update their velocities before they update their
    // positions. This way, no boids get a "head start".
    double dt = dtClock.restart().asSeconds();
    for (Boid& boid : boids)
        boid.updatePosition(dt);
}

void BoidManager::batchUpdatePositions(int offset, int batchSize, bool scatter)
{
    int visionRadius = 250;
    Boid::boidRefVec nearbyBoids;

    auto itEnd = ((offset != threadNum - 1) ? (boids.begin() + offset * batchSize + batchSize) : boids.end());
    for (auto it = boids.begin() + offset * batchSize; it != itEnd; ++it) 
    {
        /* visionRadius = boid.isPredator() ? 500 : 250; */
        nearbyBoids.clear();
        for (Boid& compBoid : boids)
            if (((*it).getPosition() - compBoid.getPosition()).length() < visionRadius
                    && compBoid.getPosition() != (*it).getPosition())
                nearbyBoids.push_back(compBoid);

        (*it).updateVelocity(nearbyBoids, scatter);
    }
}

void BoidManager::drawBoids(sf::RenderWindow& window, bool drawArrows)
{
    for (Boid& boid : boids)
        boid.draw(window, drawArrows);
}

int BoidManager::getBoidCount()
{
    return boids.size();
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
                        Vector2(viewCenter.x + viewSize.x/2 - 100, viewCenter.y + viewSize.y/2 - 50));
}
