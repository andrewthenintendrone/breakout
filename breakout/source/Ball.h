#pragma once
#include "GameObject.h"
#include "Brick.h"

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
        if (bounds.left <= 0 || bounds.left + bounds.width >= WINDOW->getSize().x)
        {
            velocity.x = -velocity.x;
        }
        // top
        if (bounds.top <= 0)
        {
            velocity.y = -velocity.y;
        }
        // bottom
        if (bounds.top + bounds.height >= WINDOW->getSize().y)
        {

        }
        // paddle
        if (bounds.intersects(paddle->getSprite().getGlobalBounds()))
        {
            // make this better
            velocity.y = -velocity.y;
        }
        //bricks
        for (unsigned int i = 0; i < bricks.size(); i++)
        {
            // if hitting a brick
            if (bricks[i]->getVisible() && bounds.intersects(bricks[i]->getSprite().getGlobalBounds()))
            {
                bounce(bricks[i]->getSprite().getGlobalBounds());
                bricks[i]->setVisible(false);
                break;
            }
        }
        transform.translate(velocity * TIME->deltaTime());
        updateTransform();
        getSprite().setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
    }

    void setPaddle(Paddle* newPaddle)
    {
        paddle = newPaddle;
    }

    void setBricks(std::vector<Brick*> newBricks)
    {
        bricks = newBricks;
    }

    // physics
    void bounce(sf::FloatRect hitRect)
    {
        sf::Vector2f myPosition = getSprite().getPosition();

        // hit from left
        if (myPosition.x < hitRect.left)
        {
            velocity.x = -velocity.x;
        }
        // hit from right
        else if (myPosition.x > hitRect.left + hitRect.width)
        {
            velocity.x = -velocity.x;
        }
        // hit from above
        else if (myPosition.y < hitRect.top)
        {
            velocity.y = -velocity.y;
        }
        // hit from below
        else if (myPosition.y > hitRect.top + hitRect.height)
        {
            velocity.y = -velocity.y;
        }
    }

private:
    std::vector<Brick*> bricks;
    sf::Vector2f velocity = sf::Vector2f(200, 200);
    Paddle* paddle;
};