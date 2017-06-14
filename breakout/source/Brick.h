#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
public:
    Brick();
    Brick(std::string& imageFileName);

    void Brick::UpdatePlaying();

    bool getVisible();

    void setVisible(bool isVisible);

private:
    bool visible = true;
};