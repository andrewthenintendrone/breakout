#pragma once
#include <vector>
#include "GameState.h"

#define GAMESTATEMANAGER GameStateManager::getInstance()

enum class GAMESTATE { MENU, SERVING, PLAYING, PAUSED, WON };

class GameStateManager
{
public:
    // constructors and destructors
    static GameStateManager* getInstance();
    GameStateManager();
    ~GameStateManager();

    // state stack management
    void pushState(GAMESTATE newState);
    void popState();

    void Update();

private:
    std::vector<GAMESTATE> currentGameStates;
};