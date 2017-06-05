#include "GameObject.h"

// default GameObject constructor
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
        m_sprite->setOrigin(m_sprite->getGlobalBounds().width / 2.0f, m_sprite->getGlobalBounds().height / 2.0f);
    }
    else
    {
        // image load error
    }
}

// handles events
void GameObject::handleInput(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        transform.translate(transform.forwardVector() * 300.0f * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        transform.rotate(-180 * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        transform.translate(transform.forwardVector() * -300.0f * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        transform.rotate(180 * deltaTime);
    }
    updateTransform();
}

// updates how the sprite looks
void GameObject::updateTransform()
{
    m_sprite->setPosition(transform.m_position);
    m_sprite->setRotation(transform.m_rotation);
    m_sprite->setScale(transform.m_scale);
}