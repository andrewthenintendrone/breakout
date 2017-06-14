#pragma once
#include "GameObject.h"
#include "Paddle.h"
#include "Brick.h"
#include "AudioManager.h"

class Ball : public GameObject
{
public:
    Ball();
    Ball(std::string& imageFileName);

    void Move();

    void Serve();

    void setPaddle(Paddle* newPaddle);

    void setBricks(std::vector<Brick*> newBricks);

    void bounce(sf::FloatRect hitRect);

private:
    std::vector<Brick*> bricks;
    sf::Vector2f velocity = sf::Vector2f(200, -200);
    Paddle* paddle;
};