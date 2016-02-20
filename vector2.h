#pragma once

class Vector2
{
public:
    Vector2(double X, double Y);
    Vector2();

    Vector2 operator + (Vector2 rightVec);
    Vector2 operator += (Vector2 rightVec);

    Vector2 operator - (Vector2 rightVec);
    Vector2 operator -= (Vector2 rightVec);

    Vector2 operator * (double rightNum);
    Vector2 operator *= (double rightNum);

    Vector2 operator / (double rightNum);
    Vector2 operator /= (double rightNum);

    bool operator == (Vector2 rightVec);
    bool operator != (Vector2 rightVec);

    double dot(Vector2 rightVec);
    double length();
    Vector2 normalized();

    void setX(double x);
    double getX();
    void setY(double y);
    double getY();

private:
    double x;
    double y;
};
