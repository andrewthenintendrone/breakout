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

#pragma region state stack management

// pushes a state onto the stack
void StateManager::pushState(STATE newState)
{
    currentStates.push_back(newState);
}

// pushes a state from the stack
void StateManager::popState()
{
    currentStates.pop_back();
}
#pragma endregion

void StateManager::update()
{
    for (unsigned int i = 0; i < currentStates.size(); i++)
    {
        switch (currentStates[i])
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
}