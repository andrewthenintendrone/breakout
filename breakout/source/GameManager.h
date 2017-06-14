#pragma once
#include <SFML\Graphics.hpp>
#include "AudioManager.h"
#include <time.h>
#include <Windows.h>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "stateManager.h"

#define GAMEMANAGER GameManager::getInstance()

class GameManager
{
public:
    static GameManager* getInstance();
    std::string getPath();
    void init();

    void updateMenu();
    void updateServing();
    void updatePaused();
    void updatePlaying();
    void updateWon();

private:
    Ball ball;
    Paddle paddle;
    std::vector<Brick*> bricks;
    sf::Text menuTextBreakOut;
    sf::Text menuTextPlay;
    sf::Text menuTextExit;
    sf::Texture brickTex;
    sf::Texture scaryTex;
    sf::Sprite scarySprite;
    sf::Font font;
};