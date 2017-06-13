#pragma once
#include "GameObject.h"
#include "Ball.h"

class Brick : public GameObject
{
public:
    // default constructor
    Brick(void)
    {
        init();
    }

    // construct with sprite
    Brick(std::string& imageFileName)
    {
        init();
        setSprite(imageFileName);
    }

    // handles events
    void Brick::Update()
    {
        if (visible)
        {
            draw();
        }
    }

    // returns true if this Brick is visible
    bool getVisible()
    {
        return visible;
    }

    // sets this brick
    void setVisible(bool isVisible)
    {
        visible = isVisible;
    }

private:
    bool visible = true;
};