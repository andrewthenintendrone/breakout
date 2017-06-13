#pragma once

class GameState
{
public:
    GameState() {}
    virtual ~GameState() = 0 {}

    virtual void Update() = 0;
    virtual void Draw() = 0;
};