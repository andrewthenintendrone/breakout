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
        velocity.x = -fabsf(velocity.x) + rand() % 10 - 5;
        AUDIOMANAGER->playBounceSound();
    }
    // top
    if (bounds.top <= 0)
    {
        velocity.y = fabsf(velocity.y) + rand() % 10 - 5;
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
        velocity.y = -fabsf(velocity.y) + rand() % 10 - 5;
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

void Ball::Serve()
{

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
        velocity.x = -velocity.x + rand() % 10 - 5;
    }
    // hit from above
    else if (myPosition.y < hitRect.top)
    {
        velocity.y = -velocity.y + rand() % 10 - 5;
    }
    // hit from right
    if (myPosition.x > hitRect.left + hitRect.width)
    {
        velocity.x = -velocity.x + rand() % 10 - 5;
    }
    // hit from below
    else if (myPosition.y > hitRect.top + hitRect.height)
    {
        velocity.y = -velocity.y + rand() % 10 - 5;
    }

    AUDIOMANAGER->playBounceSound();
}