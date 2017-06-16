#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

#define TEXTMANAGER TextManager::getInstance()

class TextManager
{
public:
    static TextManager* getInstance();

    void init(std::string& fontPath);
    void addText(std::string& newString, unsigned int newSize, sf::Vector2f newPosition, sf::Color newColor);
    sf::Text* getText(std::string& searchString);

private:
    sf::Font m_font;
    std::vector<sf::Text> m_texts;
};
