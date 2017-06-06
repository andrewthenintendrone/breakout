#pragma once
#include <SFML\Graphics.hpp>
#include "Transform.h"
#include "TimeManager.h"

class GameObject
{
public:
    // constructors and destructors
    GameObject(void);
    GameObject(std::string& imageFileName);
    virtual ~GameObject();

    // get and set sprite
    sf::Sprite& getSprite();
    void setSprite(std::string& imageFileName);
    virtual void Update(sf::RenderWindow* window) = 0 {};

    Transform transform;
    void updateTransform();
    void init();
protected:
private:
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;
};