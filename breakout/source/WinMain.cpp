#include "Game.h"
#include "GameStateManager.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    GAME->init();
    // create GameStateManager
    GameStateManager gameStateManager;
    gameStateManager.pushState(GAMESTATE::PLAYING);
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
        gameStateManager.Update();
        WINDOWMANAGER->getWindow()->display();
    }
    return 0;
}