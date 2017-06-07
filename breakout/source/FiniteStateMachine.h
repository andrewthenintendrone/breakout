#pragma once
#include "GameObject.h"
#include "State.h"

class FiniteStateMachine
{
public:
    FiniteStateMachine(int stateCount) { m_states.resize(stateCount); }
    virtual ~FiniteStateMachine() {}

    void addState(int id, State* newState) { m_states[id] = newState; }

    void forceState(int id) { m_currentState = m_states[id]; }

    void Update(GameObject* gameObject)
    {
        if (m_currentState != nullptr)
        {
            m_currentState->Update(gameObject);
        }
    }

protected:
    State* m_currentState = nullptr;
    std::vector<State*> m_states;
};