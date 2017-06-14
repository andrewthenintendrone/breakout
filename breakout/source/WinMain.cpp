#include "gameManager.h"
#include "stateManager.h"
#include "windowManager.h"
#include "timeManager.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    STATEMANAGER->changeState(STATE::MENU);
    GAMEMANAGER->init();
    sf::Event event;
    while (WINDOWMANAGER->getWindow()->isOpen())
    {
        while (WINDOWMANAGER->getWindow()->pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                WINDOWMANAGER->closeWindow();
                break;
            }
            if (event.type == sf::Event::Closed)
            {
                WINDOWMANAGER->closeWindow();
                break;
            }
        }
        TIMEMANAGER->update();
        WINDOWMANAGER->getWindow()->clear();
        STATEMANAGER->update();
        WINDOWMANAGER->getWindow()->display();
    }

    return 0;
}