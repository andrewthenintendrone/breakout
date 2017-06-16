#include "gameManager.h"
#include "stateManager.h"
#include "windowManager.h"
#include "timeManager.h"
#include "InputManager.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    STATEMANAGER->changeState(STATE::MENU);
    GAMEMANAGER->init();
    while (WINDOWMANAGER->getWindow()->isOpen())
    {
        INPUTMANAGER->update();
        TIMEMANAGER->update();
        WINDOWMANAGER->getWindow()->clear();
        STATEMANAGER->update();
        WINDOWMANAGER->getWindow()->display();
    }

    return 0;
}