#include "WindowManager.h"

// creates the render window
void WindowManager::createWindow(sf::VideoMode videoMode, sf::String title)
{
    if (m_window)
    {
        delete(m_window);
    }
    m_window = new sf::RenderWindow(videoMode, title);
}

// destroys the window and closes
void WindowManager::closeWindow()
{
    if (m_window)
    {
        m_window->close();
    }
}

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

// returns the window
sf::RenderWindow* WindowManager::getWindow()
{
    return m_window;
}

// returns the size of the window as a sf::Vector2u
sf::Vector2u WindowManager::getSize()
{
    return m_window->getSize();
}