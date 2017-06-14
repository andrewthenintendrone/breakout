#pragma once
#include <vector>

#define STATEMANAGER StateManager::getInstance()

enum class STATE { MENU, SERVING, PLAYING, PAUSED, WON };

class StateManager
{
public:
    // constructors and destructors
    static StateManager* getInstance();
    StateManager();
    ~StateManager();

    // state stack management
    void pushState(STATE newState);
    void popState();

    void update();

private:
    std::vector<STATE> currentStates;
};