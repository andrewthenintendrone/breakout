#pragma once
#include <vector>
#include "ServingState.h"
#include "PlayingState.h"
#include "PausedState.h"
#include "WonState.h"
#include "MenuState.h"

enum class GAMESTATE { MENU, SERVING, PLAYING, PAUSED, WON };

class GameStateManager
{
public:
#pragma region constructors and destructors
    GameStateManager()
    {
        fillStates();
    }

    ~GameStateManager()
    {
        for (GameState* currentGameState : allStates)
        {
            if (currentGameState)
            {
                delete currentGameState;
            }
        }
    }
#pragma endregion

#pragma region state stack management
    // adds one of each GameState type to a vector
    void fillStates()
    {
        allStates.push_back(new MenuState);
        allStates.push_back(new ServingState);
        allStates.push_back(new PlayingState);
        allStates.push_back(new PausedState);
        allStates.push_back(new WonState);
    }

    // pushes a state onto the stack
    void pushState(GAMESTATE newState)
    {
        activeStates.push_back(allStates[(int)newState]);
    }

    // pushes a state from the stack
    void popState()
    {
        activeStates.pop_back();
    }
#pragma endregion

#pragma region Update / Draw
    void Update()
    {
        for (GameState* currentState : activeStates)
        {
            if (currentState != nullptr)
            {
                currentState->Update();
            }
        }
    }

    void Draw()
    {
        for (GameState* currentState : activeStates)
        {
            if (currentState != nullptr)
            {
                currentState->Draw();
            }
        }
    }
#pragma endregion

private:
    std::vector<GameState*> allStates;
    std::vector<GameState*> activeStates;
};