#include "Brick.h"

// default constructor
Brick::Brick()
{
    init();
}

// construct with sprite
Brick::Brick(std::string& imageFileName)
{
    init();
    setSprite(imageFileName);
}

// handles events
void Brick::UpdatePlaying()
{
    if (visible)
    {
        draw();
    }
}

// returns true if this Brick is visible
bool Brick::getVisible()
{
    return visible;
}

// sets this brick
void Brick::setVisible(bool isVisible)
{
    visible = isVisible;
}