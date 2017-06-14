#pragma once
#include "GameObject.h"

class Paddle : public GameObject
{
public:
    Paddle();
    Paddle(std::string& imageFileName);
    void Control();
};