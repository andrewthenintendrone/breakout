#include "Paddle.h"
#include "InputManager.h"

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
    if (INPUTMANAGER->keyHeld(sf::Keyboard::Left) || INPUTMANAGER->keyHeld(sf::Keyboard::A))
    {
        if (getSprite().getGlobalBounds().left > 0)
        {
            getSprite().move(-600 * TIMEMANAGER->deltaTime(), 0);
        }
    }
    // right
    if(INPUTMANAGER->keyHeld(sf::Keyboard::Right) || INPUTMANAGER->keyHeld(sf::Keyboard::D))
    {
        if ((getSprite().getGlobalBounds().left + getSprite().getGlobalBounds().width) < WINDOWMANAGER->getSize().x)
        {
            getSprite().move(600 * TIMEMANAGER->deltaTime(), 0);
        }
    }

    // mouse movemenet
    //getSprite().setPosition(INPUTMANAGER->mousePosition().x, getSprite().getPosition().y);


    draw();
}