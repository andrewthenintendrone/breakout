#pragma once
#include <SFML\Graphics.hpp>
#include "Transform.h"
#include "WindowManager.h"
#include "TimeManager.h"
#include "FiniteStateMachine.h"
#include <exception>

class GameObject
{
public:
    // constructors and destructors
    GameObject();
    GameObject(std::string& imageFileName);
    virtual ~GameObject();

    // Sprite
    sf::Sprite& getSprite();
    void setSprite(std::string& imageFileName);

    void setState(State* newState);
    void draw();
    void init();
    virtual void Update() = 0;
private:
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;
    State* m_state;
};