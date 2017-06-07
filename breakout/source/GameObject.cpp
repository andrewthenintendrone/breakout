#include "GameObject.h"

// default GameObject constructor
GameObject::GameObject(void)
{
    init();
}

// construct with string of image file
GameObject::GameObject(std::string& imageFileName)
{
    init();
    setSprite(imageFileName);
}

GameObject::~GameObject()
{
    // cleanup
    if (m_texture != nullptr) { delete m_texture; }
    if (m_sprite != nullptr) { delete m_sprite; }
}

// returns the address of the GameObjects sprite
sf::Sprite& GameObject::getSprite()
{
    return *m_sprite;
}

// sets the GameObjects sprite
void GameObject::setSprite(std::string& imageFileName)
{
    if (m_texture->loadFromFile(imageFileName))
    {
        m_sprite = new sf::Sprite;
        m_sprite->setTexture(*m_texture);
        m_sprite->setOrigin(m_sprite->getGlobalBounds().width / 2.0f, m_sprite->getGlobalBounds().height / 2.0f);
    }
    else
    {
        // image load error
    }
}

// sets the GameObjects State
void GameObject::setState(State* newState)
{
    delete m_state;
    m_state = newState;
}

// updates how the sprite looks
void GameObject::updateTransform()
{
    m_sprite->setPosition(transform.m_position);
    m_sprite->setRotation(transform.m_rotation);
    m_sprite->setScale(transform.m_scale);
}

void GameObject::init()
{
    m_texture = new sf::Texture;
    m_sprite = new sf::Sprite;
    m_state = nullptr;
}