#include "Ball.h"

// default constructor
Ball::Ball()
{
    init();
}

// construct with sprite
Ball::Ball(std::string& imageFileName)
{
    init();
    setSprite(imageFileName);
}

void Ball::Move()
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
    // paddle
    if (bounds.intersects(paddle->getSprite().getGlobalBounds()))
    {
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
    draw();
}

void Ball::Serve()
{
    getSprite().setPosition(paddle->getSprite().getPosition() - sf::Vector2f(0, paddle->getSprite().getGlobalBounds().height + 10));
    draw();
}

void Ball::setPaddle(Paddle* newPaddle)
{
    paddle = newPaddle;
}

void Ball::setBricks(std::vector<Brick*> newBricks)
{
    bricks = newBricks;
}

void Ball::bounce(sf::FloatRect hitRect)
{
    sf::Vector2f myPosition = getSprite().getPosition();

    // hit from left
    if (myPosition.x < hitRect.left)
    {
        velocity.x = -velocity.x;
    }
    // hit from above
    else if (myPosition.y < hitRect.top)
    {
        velocity.y = -velocity.y;
    }
    // hit from right
    if (myPosition.x > hitRect.left + hitRect.width)
    {
        velocity.x = -velocity.x;
    }
    // hit from below
    else if (myPosition.y > hitRect.top + hitRect.height)
    {
        velocity.y = -velocity.y;
    }

    AUDIOMANAGER->playBounceSound();
}