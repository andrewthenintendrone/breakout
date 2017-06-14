#include "Game.h"
#include "GameStateManager.h"
#include "WindowManager.h"
#include "TimeManager.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    GAMESTATEMANAGER->pushState(GAMESTATE::MENU);
    GAME->init();
    while (WINDOWMANAGER->getWindow()->isOpen())
    {
        sf::Event event;
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
        TIME->Update();
        WINDOWMANAGER->getWindow()->clear();
        GAMESTATEMANAGER->Update();
        WINDOWMANAGER->getWindow()->display();
    }
    return 0;
}