#pragma once
#include <vector>

#define STATEMANAGER StateManager::getInstance()

enum class STATE { MENU, SERVING, PAUSED, PLAYING, WON };

class StateManager
{
public:
    // constructors and destructors
    static StateManager* getInstance();
    StateManager();
    ~StateManager();

    void changeState(STATE newState);

    void update();

private:
    STATE currentState;
};