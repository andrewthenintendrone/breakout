#include "GameObject.h"

// default GameObject constructor
GameObject::GameObject()
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
    if (m_texture)
    {
        delete m_texture;
    }
    if (m_sprite)
    {
        delete m_sprite;
    }
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
        m_sprite->setTexture(*m_texture);
        m_sprite->setOrigin(m_sprite->getGlobalBounds().width / 2.0f, m_sprite->getGlobalBounds().height / 2.0f);
    }
    else
    {
        throw std::exception(std::string("Failed to load image: " + imageFileName).c_str());
    }
}

// sets the GameObjects State
void GameObject::setState(State* newState)
{
    delete m_state;
    m_state = newState;
}

// updates how the sprite looks
void GameObject::draw()
{
    WindowManager::getInstance()->getWindow()->draw(*m_sprite);
}

void GameObject::init()
{
    m_texture = new sf::Texture;
    m_sprite = new sf::Sprite;
    m_state = nullptr;
}