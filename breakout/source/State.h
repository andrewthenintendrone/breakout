#pragma once
#include "Condition.h"

class State
{
public:
    virtual ~State() { for (auto t : m_transitions) delete t; }

    virtual void onEnter(GameObject* object) {}
    virtual void onExit(GameObject* object) {}

    virtual void onUpdate(GameObject* object, float dt) = 0;

    void addTransition(Transition* transition)
    {
        m_transitions.push_back(transition);
    }

    State* getNextState(GameObject* gameObject)
    {
        for (auto transition : m_transitions)
        {
            if (transition->isConditionMet(gameObject))
                return transition->getTargetState();
        }
        // no state change
        return nullptr;
    }

protected:

    std::vector<Transition*> m_transitions;
};