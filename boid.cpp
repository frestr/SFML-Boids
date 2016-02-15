#include "boid.h"
#include <cmath>
#include <iostream>

Boid::Boid(double xPos, double yPos, bool isPredator) : predator(isPredator)
{
    int size = 1;

    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(0, 0));
    shape.setPoint(1, sf::Vector2f(-7 * size, 20 * size));
    shape.setPoint(2, sf::Vector2f(7 * size, 20 * size));
    shape.setOrigin(0, 10 * size);

    sf::Color fillColor    = predator ? sf::Color(255, 0, 0) : sf::Color(0, 255,0 );
    sf::Color outlineColor = predator ? sf::Color(150, 0, 0) : sf::Color(0, 150, 0);
    shape.setFillColor(fillColor);
    shape.setOutlineColor(outlineColor);
    shape.setOutlineThickness(2);

    velocityArrow.setFillColor(sf::Color(200, 0, 0));

    position.setX(xPos);
    position.setY(yPos);
    updatePosition(0);
    updateVelocityArrow();
}

void Boid::updateVelocity(boidRefVec nearbyBoids, bool scatter)
{
    if (nearbyBoids.size() > 0)
    {
        // These are coefficients that has shown to work out well
        double c1 = 1.0/20.0;
        double c2 = 1.0/2.0;
        double c3 = 1.0/200.0;
        double c4 = 1.0/5.0;

        if (scatter)
        {
            c1 *= -2; // Go away from center (instead of towards)
            c3 /= 2;  // Do not try to align velocity as eagerly
        }
        if (predator)
            c1 *= 3;

        Vector2 towardsCenter      = rule1(nearbyBoids) * c1;
        Vector2 repellingForce     = rule2(nearbyBoids) * c2;
        Vector2 perceivedVelocity  = rule3(nearbyBoids) * c3;
        Vector2 fleeForce          = fleeFromPredators(nearbyBoids) * c4;

        velocity += towardsCenter;
        if (! predator)
        {
            velocity += repellingForce;
            velocity += perceivedVelocity;
            velocity += fleeForce;
        }
    }
    double c5 = 1.0;
    if (predator)
        c5 = 2.0;
    velocity += boundPosition() * c5;

    limitVelocity();
    updateVelocityArrow();
    shape.setRotation(getPointingAngle() + 90);
}

void Boid::updatePosition(double dt)
{
    position = position + velocity * dt;
    shape.setPosition(position.getX(), position.getY());
}

void Boid::draw(sf::RenderWindow& window, bool drawArrow)
{
    if (drawArrow)
        window.draw(velocityArrow);
    window.draw(shape);
}

Vector2 Boid::getPosition()
{
    return position;
}

Vector2 Boid::getVelocity()
{
    return velocity;
}

void Boid::setBoundingBox(Vector2 min, Vector2 max)
{
    if (min.getX() >= max.getX() || min.getY() >= max.getY())
    {
        std::cout << "Illegal bounding box: min={" << min.getX() << ":" << min.getY() << "} " <<
                                           "max={" << max.getX() << ":" << max.getY() << "}\n";
        throw "Illegal bounding box";
    }
    minBounding = min;
    maxBounding = max;
}

bool Boid::isPredator()
{
    return predator;
}

/* Rule 1: Try to fly towards the center of mass of neighbouring boids */
Vector2 Boid::rule1(boidRefVec nearbyBoids)
{
    Vector2 centerOfMass;
    for (Boid& boid : nearbyBoids)
        if (! boid.isPredator())
            centerOfMass += boid.getPosition();

    centerOfMass /= nearbyBoids.size();
    return centerOfMass - position;
}

/* Rule 2: Try to keep a distance from other boids */
Vector2 Boid::rule2(boidRefVec nearbyBoids)
{
    Vector2 repellingForce;
    for (Boid& boid : nearbyBoids)
        if ((boid.getPosition() - position).length() < 30)
            repellingForce -= boid.getPosition() - position;

    return repellingForce;
}

/* Rule 3: Try to match the velocity of nearby boids */
Vector2 Boid::rule3(boidRefVec nearbyBoids)
{
    Vector2 perceivedVelocity;
    for (Boid& boid : nearbyBoids)
        if (! boid.isPredator())
            perceivedVelocity += boid.getVelocity();

    perceivedVelocity /= nearbyBoids.size();
    return perceivedVelocity;
}

Vector2 Boid::fleeFromPredators(boidRefVec nearbyBoids)
{
    Vector2 fleeVelocity;
    int predators = 0;
    for (Boid& boid : nearbyBoids)
        if (boid.isPredator())
        {
            fleeVelocity -= (boid.getPosition() - position);
            ++predators;
        }
    if (predators == 0)
        return Vector2(0, 0);
    else
        return fleeVelocity / predators;
}

void Boid::limitVelocity()
{
    int limit = 500;
    if (velocity.length() > limit)
        velocity = (velocity / velocity.length()) * limit;
}

Vector2 Boid::boundPosition()
{
    Vector2 vel;
    if (position.getX() < minBounding.getX())
        vel.setX(20);
    else if (position.getX() > maxBounding.getX())
        vel.setX(-20);

    if (position.getY() < minBounding.getY())
        vel.setY(-20);
    else if (position.getY() > maxBounding.getY())
        vel.setY(20);
    
    return vel;
}

void Boid::updateVelocityArrow()
{
    velocityArrow.setPosition(shape.getPosition());

    double arrowLength = velocity.length() / 4;
    velocityArrow.setSize(sf::Vector2f(arrowLength, 2));

    velocityArrow.setRotation(getPointingAngle());
}

double Boid::getPointingAngle()
{
    Vector2 normVel = velocity;
    normVel.normalize();

    // SFML's rotate-function uses degrees going clockwise from 0 to <360
    double angle = atan2(normVel.getY(), normVel.getX());
    angle *= 180 / 3.14159265;  // Convert to degrees
    angle *= -1;  // Flip

    return angle;
}
