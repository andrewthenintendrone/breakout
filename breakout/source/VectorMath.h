#pragma once
#include <SFML\Graphics.hpp>
#include <cmath>

#define PI 3.14159f

// converts degrees to radians
float degreesToRadians(const float degrees)
{
    return degrees * PI / 180.0f;
}

// converts radians to degrees
float radiansToDegrees(const float radians)
{
    return radians * 180.0f / PI;
}

// returns a rotated Vector2
sf::Vector2f getRotationVector(const float rotation)
{
    float a = degreesToRadians(rotation);
    return sf::Vector2f(cosf(a), sinf(a));
}

// returns the normalized version of the Vector2
sf::Vector2f normalized(const sf::Vector2f& rhs)
{
    float magnitude = sqrtf((rhs.x * rhs.x) + (rhs.y * rhs.y));
    return rhs / magnitude;
}