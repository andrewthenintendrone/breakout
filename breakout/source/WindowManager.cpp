#include "WindowManager.h"

// creates the render Window
void WindowManager::createWindow(sf::VideoMode videoMode, sf::String title)
{
    if (m_window)
    {
        delete(m_window);
    }
    m_window = new sf::RenderWindow(videoMode, title, sf::Style::Titlebar | sf::Style::Close);
}

// destroys the Window and closes
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

// sets the Window
void WindowManager::setWindow(sf::RenderWindow* Window)
{
    m_window = Window;
}

// returns the Window
sf::RenderWindow* WindowManager::getWindow()
{
    return m_window;
}

// returns the size of the Window as a sf::Vector2u
sf::Vector2u WindowManager::getSize()
{
    return m_window->getSize();
}