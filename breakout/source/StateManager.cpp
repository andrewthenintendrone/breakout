#include "stateManager.h"
#include "gameManager.h"

#pragma region constructors and destructors
StateManager* StateManager::getInstance()
{
    static StateManager instance;
    return &instance;
}

StateManager::StateManager()
{
    
}

StateManager::~StateManager()
{

}
#pragma endregion

void StateManager::changeState(STATE newState)
{
    currentState = newState;
}

void StateManager::update()
{
    switch (currentState)
    {
    case STATE::MENU:
        GAMEMANAGER->updateMenu();
        break;
    case STATE::SERVING:
        GAMEMANAGER->updateServing();
        break;
    case STATE::PLAYING:
        GAMEMANAGER->updatePlaying();
        break;
    case STATE::PAUSED:
        GAMEMANAGER->updatePaused();
        break;
    case STATE::WON:
        GAMEMANAGER->updateWon();
        break;
    default:
        break;
    }
}