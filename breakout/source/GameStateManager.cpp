#include "GameStateManager.h"

void GameStateManager::registerState(int id, GameState* state)
{
    m_registeredStates.push_back(m_stateStack[id]);
}

void GameStateManager::pushState(int id)
{
    m_stateStack.push_back(m_registeredStates[id]);
}

void GameStateManager::popState()
{
    m_stateStack.pop_back();
}

void GameStateManager::update(float deltaTime)
{

}

void GameStateManager::draw()
{

}
