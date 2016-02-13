#include "boid.h"
#include <cmath>
#include <iostream>

Boid::Boid(double xPos, double yPos, double size)
{
    if (size <= 0)
        size = 1;

    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(0, 0));
    shape.setPoint(1, sf::Vector2f(-10 * size, 30 * size));
    shape.setPoint(2, sf::Vector2f(10 * size, 30 * size));
    shape.setOrigin(0, 15 * size);

    shape.setFillColor(sf::Color(0, 255, 0));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(0, 150, 0));

    velocityArrow.setFillColor(sf::Color(200, 0, 0));

    position.setX(xPos);
    position.setY(yPos);
    updatePosition(0);
    updateVelocityArrow();
}

void Boid::updateVelocity(std::vector<Boid>& nearbyBoids, bool scatter)
{
    if (nearbyBoids.size() > 0)
    {
        // These are coefficients that has shown to work out well
        double c1 = 1.0/30.0;
        double c2 = 1.0/2.0;
        double c3 = 1.0/200.0;

        if (scatter)
        {
            c1 *= -2; // Go away from center (instead of towards)
            c3 /= 2;  // Do not try to align velocity as eagerly
        }

        Vector2 towardsCenter      = rule1(nearbyBoids) * c1;
        Vector2 repellingForce     = rule2(nearbyBoids) * c2;
        Vector2 perceivedVelocity  = rule3(nearbyBoids) * c3;

        velocity = velocity + towardsCenter + repellingForce + perceivedVelocity;
    }
    velocity += boundPosition();
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

/* Rule 1: Try to fly towards the center of mass of neighbouring boids */
Vector2 Boid::rule1(std::vector<Boid>& nearbyBoids)
{
    Vector2 centerOfMass;
    for (Boid& boid : nearbyBoids)
        centerOfMass += boid.getPosition();

    centerOfMass /= nearbyBoids.size();
    return centerOfMass - position;
}

/* Rule 2: Try to keep a distance from other boids */
Vector2 Boid::rule2(std::vector<Boid>& nearbyBoids)
{
    Vector2 repellingForce;
    for (Boid& boid : nearbyBoids)
        if ((boid.getPosition() - position).length() < 40)
            repellingForce -= boid.getPosition() - position;

    return repellingForce;
}

/* Rule 3: Try to match the velocity of nearby boids */
Vector2 Boid::rule3(std::vector<Boid>& nearbyBoids)
{
    Vector2 perceivedVelocity;
    for (Boid& boid : nearbyBoids)
        perceivedVelocity += boid.getVelocity();

    perceivedVelocity /= nearbyBoids.size();
    return perceivedVelocity;
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

    double arrowLength = velocity.length() / 2;
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
    if (angle >= 180 && angle < 360)
        angle += 360;

    return angle;
}
