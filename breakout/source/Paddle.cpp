#include "Paddle.h"

// default constructor
Paddle::Paddle()
{
    init();
}

// construct with sprite
Paddle::Paddle(std::string& imageFileName)
{
    init();
    setSprite(imageFileName);
}

// handles events
void Paddle::Control()
{
    // left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (getSprite().getGlobalBounds().left > 0)
        {
            getSprite().move(-600 * TIME->deltaTime(), 0);
        }
    }
    // right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if ((getSprite().getGlobalBounds().left + getSprite().getGlobalBounds().width) < WINDOWMANAGER->getSize().x)
        {
            getSprite().move(600 * TIME->deltaTime(), 0);
        }
    }
    draw();
}