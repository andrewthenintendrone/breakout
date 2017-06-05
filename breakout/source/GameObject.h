#pragma once
#include <SFML\Graphics.hpp>

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
protected:
    void handleEvent(sf::Event currentEvent);
private:
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;
    // Transform
};