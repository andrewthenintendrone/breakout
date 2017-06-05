#include "Transform.h"
#include "VectorMath.h"

// default Transform constructor
Transform::Transform()
{
    m_position = sf::Vector2f(0, 0);
    m_rotation = 0;
    m_scale = sf::Vector2f(1, 1);
}

// destructor
Transform::~Transform()
{

}

// translates this GameObject using a Vector2
void Transform::translate(sf::Vector2f& translationAmount)
{
    m_position += translationAmount;
}

// translates this GameObject using two floats
void Transform::translate(float xAmount, float yAmount)
{
    m_position.x += xAmount;
    m_position.y += yAmount;
}

// rotates this GameObject
void Transform::rotate(float angle)
{
    m_rotation += angle;
}

// scales this GameObject using a Vector2
void Transform::scale(sf::Vector2f& scaleAmount)
{
    m_scale += scaleAmount;
}

// scales this GameObject using two floats
void Transform::scale(float xAmount, float yAmount)
{
    m_scale.x += xAmount;
    m_scale.y += yAmount;
}

// returns a Vector pointing forward from this Transform
sf::Vector2f Transform::forwardVector()
{
    return (normalized(getRotationVector(m_rotation)));
}