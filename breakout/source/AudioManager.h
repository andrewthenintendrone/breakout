#pragma once
#include <SFML\\Audio.hpp>
#include <string>

#define AUDIOMANAGER AudioManager::getInstance()

class AudioManager
{
public:
    static AudioManager* getInstance();
    AudioManager();
    ~AudioManager();
    void setMusic(std::string& soundFileName);
    void setBounceSound(std::string& soundFileName);
    void playMusic();
    void playBounceSound();

private:
    sf::Music* m_music;
    sf::SoundBuffer* m_bounceSoundBuffer;
    sf::Sound* m_bounceSound;
};