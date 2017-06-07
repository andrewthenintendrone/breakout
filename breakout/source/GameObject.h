#pragma once
#include <SFML\Graphics.hpp>
#include "Transform.h"
#include "WindowManager.h"
#include "TimeManager.h"
#include "State.h"

class GameObject
{
public:
    // constructors and destructors
    GameObject(void);
    GameObject(std::string& imageFileName);
    virtual ~GameObject();

    // transform
    Transform transform;

    // Sprite
    sf::Sprite& getSprite();
    void setSprite(std::string& imageFileName);

    void setState(State* newState);
    virtual void Update() = 0 {};
    void updateTransform();
    void init();
protected:
private:
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;
    State* m_state;
};