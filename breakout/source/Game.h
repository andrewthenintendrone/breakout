#pragma once
#include <SFML\Graphics.hpp>
#include "AudioManager.h"
#include <time.h>
#include <Windows.h>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "GameStateManager.h"

#define GAME Game::getInstance()

class Game
{
public:
    static Game* getInstance();
    std::string getPath();
    void init();

    void UpdateMenu();
    void UpdateServing();
    void UpdatePlaying();
    void UpdatePaused();
    void UpdateWon();

private:
    Ball ball;
    Paddle paddle;
    std::vector<Brick*> bricks;
    sf::Text menuTextBreakOut;
    sf::Text menuTextPlay;
    sf::Text menuTextExit;
    sf::Texture brickTex;
    sf::Font font;
};