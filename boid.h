#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "vector2.h"

class Boid
{
public:
    typedef std::reference_wrapper<Boid> boidRef;
    typedef std::vector<boidRef> boidRefVec;

    Boid(double xPos, double yPos, double size=1.0);

    void updateVelocity(boidRefVec nearbyBoids, bool scatter=false);
    void updatePosition(double dt);

    void draw(sf::RenderWindow& window, bool drawArrow = false);
    Vector2 getPosition();
    Vector2 getVelocity();
    void setBoundingBox(Vector2 min, Vector2 max);

private:
    Vector2 rule1(boidRefVec nearbyBoids);
    Vector2 rule2(boidRefVec nearbyBoids);
    Vector2 rule3(boidRefVec nearbyBoids);
    
    void limitVelocity();
    Vector2 boundPosition();
    void updateVelocityArrow();
    double getPointingAngle();

    sf::ConvexShape shape;
    sf::RectangleShape velocityArrow;
    Vector2 position;
    Vector2 velocity;

    Vector2 minBounding;
    Vector2 maxBounding; 
};
