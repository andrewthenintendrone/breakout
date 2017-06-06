#pragma once
#include <SFML\Graphics.hpp>

#define TIME TimeManager::getInstance()

// singleton
class TimeManager
{
public:
    static TimeManager* getInstance();

    float deltaTime();
    void Update();
private:
    sf::Clock m_clock;
    float m_deltaTime;
};