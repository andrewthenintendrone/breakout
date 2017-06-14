#include "AudioManager.h"

AudioManager* AudioManager::getInstance()
{
    static AudioManager instance;
    return &instance;
}

AudioManager::AudioManager()
{
    m_music = new sf::Music;
    m_bounceSoundBuffer = new sf::SoundBuffer;
    m_bounceSound = new sf::Sound;
    m_scaryBuffer = new sf::SoundBuffer;
    m_scarySound = new sf::Sound;
}

AudioManager::~AudioManager()
{
    if (m_music) { delete m_music; }
    if (m_bounceSoundBuffer) { delete m_bounceSoundBuffer; }
    if (m_bounceSound) { delete m_bounceSound; }
    if (m_scaryBuffer) { delete m_scaryBuffer; }
    if (m_scarySound) { delete m_scarySound; }
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

void AudioManager::setScarySound(std::string& soundFileName)
{
    m_scaryBuffer->loadFromFile(soundFileName);
    if (m_scarySound != nullptr)
    {
        delete m_scarySound;
    }
    m_scarySound = new sf::Sound(*m_scaryBuffer);
}

// plays the music on loop
void AudioManager::playMusic()
{
    if (m_music != nullptr)
    {
        m_music->play();
    }
}

// stops the music
void AudioManager::stopMusic()
{
    if (m_music != nullptr)
    {
        m_music->stop();
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

// plays the scary sound effect once
void AudioManager::playScarySound()
{
    if (m_scarySound != nullptr)
    {
        m_scarySound->play();
    }
}