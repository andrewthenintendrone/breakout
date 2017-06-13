#pragma once
#include <SFML\Graphics.hpp>
#include <time.h>
#include <Windows.h>
#include "WindowManager.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "AudioManager.h"

#define GAME Game::getInstance()

// returns path to the executable
std::string getPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

class Game
{
public:
    static Game* getInstance()
    {
        static Game gsm;
        return &gsm;
    }

    void init()
    {
        try
        {
            // seed random number generator
            srand((unsigned int)time(NULL));

            // create the window
            WINDOWMANAGER->createWindow(sf::VideoMode(1280, 720), "Breakout");

            // add Audio
            AUDIOMANAGER->setMusic(getPath() + "\\resources\\audio\\music.ogg");
            AUDIOMANAGER->setBounceSound(getPath() + "\\resources\\audio\\bounce.wav");
            AUDIOMANAGER->playMusic();

            // load font
            font.loadFromFile(getPath() + "\\resources\\font\\OCRAEXT.ttf");

            // set up text
            text.setFont(font);
            text.setString("it was never seen again...");
            text.setCharacterSize(50);
            text.setFillColor(sf::Color(128, 0, 255, 255));

            // start with 0 points
            unsigned int points = 0;

            // create paddle
            paddle.setSprite(getPath() + "\\resources\\graphics\\paddle.png");
            paddle.getSprite().move(WINDOWMANAGER->getSize().x / 2.0f, WINDOWMANAGER->getSize().y - (paddle.getSprite().getGlobalBounds().height / 2.0f));

            // create ball
            ball.setSprite(getPath() + "\\resources\\graphics\\ball.png");
            ball.getSprite().move(15, 31);
            ball.setPaddle(&paddle);

            // create bricks
            brickTex.loadFromFile(getPath() + "\\resources\\graphics\\brick.png");

            for (unsigned int i = 0; i < 10; i++)
            {
                for (unsigned int j = 0; j < 4; j++)
                {
                    if ((i % 2 == 0) ^ (j % 2 == 0))
                    {
                        Brick* newBrick(new Brick());
                        newBrick->getSprite().setTexture(brickTex);
                        newBrick->getSprite().move(100 + i * 100.0f, 100 + j * 100.0f);
                        bricks.push_back(newBrick);
                    }
                }
            }
            ball.setBricks(bricks);
        }
        catch (std::exception e)
        {
            MessageBox(NULL, e.what(), "", MB_OK);
        }
    }

    void UpdatePlaying()
    {
        ball.Update();
        paddle.Update();
        for (unsigned int i = 0; i < bricks.size(); i++)
        {
            bricks[i]->Update();
        }
        if (ball.getSprite().getGlobalBounds().top >= WINDOWMANAGER->getSize().y)
        {
            WINDOWMANAGER->getWindow()->draw(text);
        }
    }

private:
    Ball ball;
    Paddle paddle;
    std::vector<Brick*> bricks;
    sf::Text text;
    sf::Texture brickTex;
    sf::Font font;
};