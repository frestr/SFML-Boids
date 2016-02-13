#include "vector2.h"
#include <cmath>

Vector2::Vector2(double X, double Y) : x(X), y(Y) {}
Vector2::Vector2() : Vector2(0, 0) {}

Vector2 Vector2::operator + (Vector2 rightVec)
{
    return Vector2(x + rightVec.x, y - rightVec.y);
}

Vector2 Vector2::operator += (Vector2 rightVec)
{
    this->x += rightVec.x;
    this->y += rightVec.y;
    return *this;
}

Vector2 Vector2::operator - (Vector2 rightVec)
{
    return Vector2(x - rightVec.x, y - rightVec.y);
}

Vector2 Vector2::operator -= (Vector2 rightVec)
{
    this->x -= rightVec.x;
    this->y -= rightVec.y;
    return *this;
}

Vector2 Vector2::operator * (double rightNum)
{
    return Vector2(x * rightNum, y * rightNum);
}

Vector2 Vector2::operator *= (double rightNum)
{
    this->x *= rightNum;
    this->y *= rightNum;
    return *this;
}

Vector2 Vector2::operator / (double rightNum)
{
    return Vector2(x / rightNum, y / rightNum);
}

Vector2 Vector2::operator /= (double rightNum)
{
    this->x /= rightNum;
    this->y /= rightNum;
    return *this;
}

double Vector2::dot(Vector2 rightVec)
{
    return x*rightVec.x + y*rightVec.y;
}

double Vector2::length()
{
    return sqrt(x*x + y*y);
}

void Vector2::normalize()
{
    double len = length();
    if (len == 0)
        len = 1;
    x /= len;
    y /= len;
}

void Vector2::setX(double x)
{
    this->x = x;
}

double Vector2::getX()
{
    return x;
}

void Vector2::setY(double y)
{
    this->y = y;
}

double Vector2::getY()
{
    return y;
}
