#pragma once
#include "Game.h"

class PlayingState : public GameState
{
public:
    void Update()
    {
        GAME->UpdatePlaying();
    }

    void Draw()
    {

    }
};