#pragma once
class GameObject;

// game State class
class State
{
public:
    virtual ~State() {}
    virtual void Update(GameObject* object) = 0 {};
};