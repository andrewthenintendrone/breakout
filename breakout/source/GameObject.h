#pragma once
#include <SFML\Graphics.hpp>
#include "Transform.h"

class GameObject
{
public:
    // constructors and destructors
    GameObject(void);
    GameObject(std::string& imageFileName);
    ~GameObject();

    // get and set sprite
    sf::Sprite& getSprite();
    void setSprite(std::string& imageFileName);
    void handleInput(float deltaTime);

    Transform transform;
protected:
private:
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;

    void updateTransform();
};