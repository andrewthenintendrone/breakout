#pragma once
#include <SFML\Graphics.hpp>

#define INPUTMANAGER InputManager::getInstance()

class InputManager
{
public:
    static InputManager* getInstance();

    bool keyHeld(sf::Keyboard::Key checkKey);
    bool keyPressed(sf::Keyboard::Key checkKey);
    bool keyReleased(sf::Keyboard::Key checkKey);

    bool mouseButtonHeld(sf::Mouse::Button checkButton);
    bool mouseButtonPressed(sf::Mouse::Button checkButton);
    bool mouseButtonReleased(sf::Mouse::Button checkButton);
    sf::Vector2f mousePosition();

    void update();

private:
    sf::Event m_event;
};