#include "TimeManager.h"

TimeManager* TimeManager::getInstance()
{
    static TimeManager instance;

    return &instance;
}

// returns deltaTime
float TimeManager::deltaTime()
{
    return m_deltaTime;
}

// updates m_deltaTime
void TimeManager::Update()
{
    m_deltaTime = m_clock.getElapsedTime().asSeconds();
    m_clock.restart();
}