#pragma once
#include "GameObject.h"

class Plane : public GameObject
{
public:
    // default constructor
    Plane(void)
    {
        init();
    }

    // construct with sprite
    Plane(std::string& imageFileName)
    {
        init();
        setSprite(imageFileName);
    }

    // handles events
    void Plane::Update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            transform.translate(transform.forwardVector() * 360.0f * TIME->deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            transform.rotate(-360 * TIME->deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            transform.translate(transform.forwardVector() * -360.0f * TIME->deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            transform.rotate(360 * TIME->deltaTime);
        }
        updateTransform();
    }
};