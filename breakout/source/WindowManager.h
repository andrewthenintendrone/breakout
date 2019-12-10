#pragma once
#include <SFML\Graphics.hpp>
#include <string>

#define WINDOWMANAGER WindowManager::getInstance()

// singleton
class WindowManager
{
public:
    void createWindow(sf::VideoMode videoMode, sf::String title);
    static WindowManager* getInstance();

    void setWindow(sf::RenderWindow* window);
    sf::RenderWindow* getWindow();
    sf::Vector2u getSize();

    void closeWindow();
private:
    sf::RenderWindow* m_window;
};