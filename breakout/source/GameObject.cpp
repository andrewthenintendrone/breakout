#include "GameObject.h"

GameObject::GameObject(std::string& imageFileName) : m_texture(nullptr), m_sprite(nullptr)
{
    m_texture = new sf::Texture;
    if (m_texture->loadFromFile(imageFileName))
    {
        m_texture->loadFromFile(imageFileName);
        m_sprite = new sf::Sprite;
        m_sprite->setTexture(*m_texture);
    }
    else
    {
        // failed to load image error
    }
}

GameObject::~GameObject()
{
    // cleanup
    if (m_texture != nullptr) { delete m_texture; }
    if (m_sprite != nullptr) { delete m_sprite; }
}

sf::Sprite& GameObject::getSprite()
{
    return *m_sprite;
}