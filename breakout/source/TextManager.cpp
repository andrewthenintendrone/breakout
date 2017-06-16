#include "TextManager.h"

TextManager* TextManager::getInstance()
{
    static TextManager instance;
    return &instance;
}

void TextManager::init(std::string& fontPath)
{
    m_font.loadFromFile(fontPath);
}

void TextManager::addText(std::string& newString, unsigned int newSize, sf::Vector2f newPosition, sf::Color newColor)
{
    sf::Text newText;
    newText.setFont(m_font);
    newText.setString(newString);
    newText.setCharacterSize(newSize);
    newText.setFillColor(newColor);
    newText.setPosition(newPosition);
    m_texts.push_back(newText);
}

// returns the wanted text
sf::Text* TextManager::getText(std::string& searchString)
{
    for(unsigned int i = 0; i < m_texts.size(); i++)
    {
        if (m_texts[i].getString() == searchString)
        {
            return &m_texts[i];
        }
    }
    // this should not happen
    return &m_texts[0];
}