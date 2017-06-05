#pragma once

#include <SFML\Graphics.hpp>


class Transform
{
public:
    Transform();
    ~Transform();

    void translate(sf::Vector2f& translationAmount);
    void translate(float xAmount, float yAmount);
    void rotate(float angle);
    void scale(sf::Vector2f& scaleAmount);
    void scale(float xAmount, float yAmount);

    sf::Vector2f m_position;
    float m_rotation;
    sf::Vector2f m_scale;

    sf::Vector2f forwardVector();

protected:

private:
};