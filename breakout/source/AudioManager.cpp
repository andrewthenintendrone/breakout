#include "AudioManager.h"

AudioManager* AudioManager::getInstance()
{
    static AudioManager audioManager;
    return &audioManager;
}

AudioManager::AudioManager()
{
    m_music = new sf::Music;
    m_bounceSoundBuffer = new sf::SoundBuffer;
    m_bounceSound = new sf::Sound;
}

AudioManager::~AudioManager()
{
    if (m_music) { delete m_music; }
    if (m_bounceSoundBuffer) { delete m_bounceSoundBuffer; }
    if (m_bounceSound) { delete m_bounceSound; }
}

void AudioManager::setMusic(std::string& soundFileName)
{
    m_music->setLoop(true);
    m_music->openFromFile(soundFileName);
}

void AudioManager::setBounceSound(std::string& soundFileName)
{
    m_bounceSoundBuffer->loadFromFile(soundFileName);
    if (m_bounceSound != nullptr)
    {
        delete m_bounceSound;
    }
    m_bounceSound = new sf::Sound(*m_bounceSoundBuffer);
}

// plays the music on loop
void AudioManager::playMusic()
{
    if (m_music != nullptr)
    {
        m_music->play();
    }
}

// plays the ball bounce sound effect once
void AudioManager::playBounceSound()
{
    if (m_bounceSound != nullptr)
    {
        m_bounceSound->play();
    }
}