#pragma once
#include "GameObject.h"
#include "Paddle.h"
#include "Brick.h"
#include "AudioManager.h"

enum class ballStates { serving, moving };

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

        // left side
        if (bounds.left <= 0)
        {
            velocity.x = fabsf(velocity.x);
            AUDIOMANAGER->playBounceSound();
        }
        // right side
        if (bounds.left + bounds.width >= WindowManager::getInstance()->getSize().x)
        {
            velocity.x = -fabsf(velocity.x);
            AUDIOMANAGER->playBounceSound();
        }
        // top
        if (bounds.top <= 0)
        {
            velocity.y = fabsf(velocity.y);
            AUDIOMANAGER->playBounceSound();
        }
        // bottom
        if (bounds.top + bounds.height >= WindowManager::getInstance()->getSize().y)
        {

        }
        // paddle
        if (bounds.intersects(paddle->getSprite().getGlobalBounds()))
        {
            // make this better
            velocity.y = -fabsf(velocity.y);
            AUDIOMANAGER->playBounceSound();
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
        getSprite().move(velocity * TIME->deltaTime());
        if (bounds.top <= WindowManager::getInstance()->getSize().y)
        {
            draw();
        }
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

        AUDIOMANAGER->playBounceSound();
    }

private:
    std::vector<Brick*> bricks;
    sf::Vector2f velocity = sf::Vector2f(200, 200);
    Paddle* paddle;
};