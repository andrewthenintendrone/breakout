#include "WindowManager.h"

WindowManager* WindowManager::getInstance()
{
    static WindowManager instance;

    return &instance;
}

// sets the window
void WindowManager::setWindow(sf::RenderWindow* window)
{
    m_window = window;
}

// gets the window
sf::RenderWindow* WindowManager::getWindow()
{
    return m_window;
}