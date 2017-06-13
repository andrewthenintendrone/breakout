#pragma once
#include <SFML\\Audio.hpp>

#define AUDIOMANAGER AudioManager::getInstance()
class AudioManager
{
public:
    static AudioManager* getInstance()
    {
        static AudioManager audioManager;
        return &audioManager;
    }

    // plays the music on loop
    void playMusic()
    {
        if (m_music != nullptr)
        {
            m_music->play();
        }
    }

    // plays the ball bounce sound effect once
    void playBounceSound()
    {
        if (m_bounceSound != nullptr)
        {
            m_bounceSound->play();
        }
    }

    void setMusic(std::string& soundFileName)
    {
        m_music->setLoop(true);
        m_music->openFromFile(soundFileName);
    }

    void setBounceSound(std::string& soundFileName)
    {
        m_bounceSoundBuffer->loadFromFile(soundFileName);
        if (m_bounceSound != nullptr)
        {
            delete m_bounceSound;
        }
        m_bounceSound = new sf::Sound(*m_bounceSoundBuffer);
    }

private:
    sf::Music* m_music = new sf::Music;
    sf::SoundBuffer* m_bounceSoundBuffer = new sf::SoundBuffer;
    sf::Sound* m_bounceSound = new sf::Sound;
};