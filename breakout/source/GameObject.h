#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
    GameObject(std::string& imageFileName);
    ~GameObject();

    sf::Sprite& getSprite();
protected:

private:
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;
    // Transform
};