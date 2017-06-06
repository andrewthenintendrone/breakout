#pragma once
#include <SFML\Graphics.hpp>

#define WINDOW WindowManager::getInstance()

// singleton
class WindowManager
{
public:
    static WindowManager* getInstance();

    void setWindow(sf::RenderWindow* window);
    sf::RenderWindow* getWindow();
private:
    sf::RenderWindow* m_window;
};