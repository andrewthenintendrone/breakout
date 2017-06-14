#include "GameStateManager.h"
#include "Game.h"

#pragma region constructors and destructors
GameStateManager* GameStateManager::getInstance()
{
    static GameStateManager gsm;
    return &gsm;
}

GameStateManager::GameStateManager()
{
    
}

GameStateManager::~GameStateManager()
{

}
#pragma endregion

#pragma region state stack management

// pushes a state onto the stack
void GameStateManager::pushState(GAMESTATE newState)
{
    currentGameStates.push_back(newState);
}

// pushes a state from the stack
void GameStateManager::popState()
{
    currentGameStates.pop_back();
}
#pragma endregion

void GameStateManager::Update()
{
    for (int i = 0; i < currentGameStates.size(); i++)
    {
        switch (currentGameStates[i])
        {
        case GAMESTATE::MENU:
            GAME->UpdateMenu();
            break;
        case GAMESTATE::SERVING:
            GAME->UpdateServing();
            break;
        case GAMESTATE::PLAYING:
            GAME->UpdatePlaying();
            break;
        case GAMESTATE::PAUSED:
            GAME->UpdatePaused();
            break;
        case GAMESTATE::WON:
            GAME->UpdateWon();
            break;
        default:
            break;
        }
    }
}