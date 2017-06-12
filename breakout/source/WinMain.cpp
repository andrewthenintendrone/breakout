#include "GameManager.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    GameManager::getInstance()->runGame();
    return 0;
}