#include "GameObject.h"

// default constructor
GameObject::GameObject() : m_texture(new sf::Texture), m_sprite(new sf::Sprite)
{

}

// construct with string of image file
GameObject::GameObject(std::string& imageFileName) : m_texture(new sf::Texture), m_sprite(new sf::Sprite)
{
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
    }
    else
    {
        // image load error
    }
}

// handles events
void handleEvent(sf::Event currentEvent)
{
    switch (currentEvent.key.code)
    {
    case sf::Keyboard::W:

        break;

    case sf::Keyboard::A:

        break;

    case sf::Keyboard::S:

        break;

    case sf::Keyboard::D:

        break;
    }
}