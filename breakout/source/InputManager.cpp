#include "InputManager.h"
#include "WindowManager.h"

InputManager* InputManager::getInstance()
{
    static InputManager instance;
    return &instance;
}

// return true if the specified key is currently held
bool InputManager::keyHeld(sf::Keyboard::Key checkKey)
{
    return (sf::Keyboard::isKeyPressed(checkKey));
}

// return true if the specified key has just been pressed
bool InputManager::keyPressed(sf::Keyboard::Key checkKey)
{
    return ((m_event.type == sf::Event::KeyPressed) && (m_event.key.code == checkKey));
}

// return true if the specified key has just been released
bool InputManager::keyReleased(sf::Keyboard::Key checkKey)
{
    return ((m_event.type == sf::Event::KeyReleased) && (m_event.key.code == checkKey));
}

// returns true if the specified mouse button is down
bool InputManager::mouseButtonHeld(sf::Mouse::Button checkButton)
{
    return (sf::Mouse::isButtonPressed(checkButton));
}

// returns true if the specified mouse button has just been pressed
bool InputManager::mouseButtonPressed(sf::Mouse::Button checkButton)
{
    return ((m_event.type == sf::Event::MouseButtonPressed) && (m_event.mouseButton.button == checkButton));
}

// returns true if the specified mouse button has just been released
bool InputManager::mouseButtonReleased(sf::Mouse::Button checkButton)
{
    return ((m_event.type == sf::Event::MouseButtonReleased) && (m_event.mouseButton.button == checkButton));
}

// returns a vector 2 of the current position
sf::Vector2f InputManager::mousePosition()
{
    return sf::Vector2f(sf::Mouse::getPosition(*WINDOWMANAGER->getWindow()));
}

// handles global inputs
void InputManager::update()
{
    if (WINDOWMANAGER->getWindow()->pollEvent(m_event))
    {
        if ((m_event.type == sf::Event::KeyPressed) && (m_event.key.code == sf::Keyboard::Escape))
        {
            WINDOWMANAGER->closeWindow();
        }
        if (m_event.type == sf::Event::Closed)
        {
            WINDOWMANAGER->closeWindow();
        }
    }
}