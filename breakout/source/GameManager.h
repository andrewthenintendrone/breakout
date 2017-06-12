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

#define GAMEMANAGER GameManager::getInstance()

// returns path to the executable
std::string getPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

class GameManager
{
public:
    static GameManager* getInstance()
    {
        static GameManager gsm;
        return &gsm;
    }

    void runGame()
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
        sf::Font font;
        font.loadFromFile(getPath() + "\\resources\\font\\OCRAEXT.ttf");

        // set up text
        sf::Text text;
        text.setFont(font);
        text.setString("it was never seen again...");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color(128, 0, 255, 255));

        // start with 0 points
        unsigned int points = 0;

        // create paddle
        Paddle paddle(getPath() + "\\resources\\graphics\\paddle.png");
        paddle.transform.translate(WINDOWMANAGER->getSize().x / 2.0f, WINDOWMANAGER->getSize().y - (paddle.getSprite().getGlobalBounds().height / 2.0f));

        // create ball
        Ball ball(getPath() + "\\resources\\graphics\\ball.png");
        ball.transform.translate(14, 14);
        ball.setPaddle(&paddle);

        // create bricks
        std::vector<Brick*> bricks;
        sf::Texture brickTex;
        brickTex.loadFromFile(getPath() + "\\resources\\graphics\\brick_small.png");
        for (unsigned int i = 0; i < 12; i++)
        {
            for (unsigned int j = 0; j < 8; j++)
            {
                if ((i % 2 == 0) ^ (j % 2 == 0))
                {
                    Brick* newBrick(new Brick());
                    newBrick->getSprite().setTexture(brickTex);
                    newBrick->transform.translate(40 + i * 100.0f, 80 + j * 50.0f);
                    newBrick->updateTransform();
                    bricks.push_back(newBrick);
                }
            }
        }
        ball.setBricks(bricks);

        // game loop
        while (WINDOWMANAGER->getWindow()->isOpen())
        {
            sf::Event event;
            while (WINDOWMANAGER->getWindow()->pollEvent(event))
            {
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                {
                    WINDOWMANAGER->closeWindow();
                    break;
                }
                if (event.type == sf::Event::Closed)
                {
                    WINDOWMANAGER->closeWindow();
                    break;
                }
            }
            TIME->Update();
            WINDOWMANAGER->getWindow()->clear();
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
            WINDOWMANAGER->getWindow()->display();
        }
    }
};