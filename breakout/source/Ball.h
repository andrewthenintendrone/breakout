#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:
    // default constructor
    Ball(void)
    {
        init();
    }

    // construct with sprite
    Ball(std::string& imageFileName)
    {
        init();
        setSprite(imageFileName);
    }

    // handles events
    void Ball::Update()
    {
        sf::FloatRect bounds = getSprite().getGlobalBounds();
        // sides
        if (bounds.left <= 0 || bounds.left + bounds.width >= 1280)
        {
            xVelocity = -xVelocity;
        }
        // top
        if (bounds.top <= 0)
        {
            yVelocity = -yVelocity;
        }
        // bottom
        if (bounds.top + bounds.height >= 720)
        {

        }
        if (bounds.intersects(paddle->getSprite().getGlobalBounds()))
        {
            yVelocity = -yVelocity;
        }
        transform.translate(xVelocity * TIME->deltaTime(), yVelocity * TIME->deltaTime());
        updateTransform();
    }

    void setPaddle(Paddle* newPaddle)
    {
        paddle = newPaddle;
    }

private:
    float xVelocity = 200;
    float yVelocity = 200;
    Paddle* paddle;
};