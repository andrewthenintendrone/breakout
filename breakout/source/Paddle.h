#pragma once
#include "GameObject.h"

class Paddle : public GameObject
{
public:
    // default constructor
    Paddle(void)
    {
        init();
    }

    // construct with sprite
    Paddle(std::string& imageFileName)
    {
        init();
        setSprite(imageFileName);
    }

    // handles events
    void Paddle::Update()
    {
        // left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (getSprite().getGlobalBounds().left > 0) 
            {
                transform.translate(-600 * TIME->deltaTime(), 0);
            }
        }
        // right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if ((getSprite().getGlobalBounds().left + getSprite().getGlobalBounds().width) < WINDOWMANAGER->getSize().x)
            {
                transform.translate(600 * TIME->deltaTime(), 0);
            }
        }
        updateTransform();
    }
};