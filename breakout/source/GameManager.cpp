#include "GameManager.h"
#include "InputManager.h"
#include "TextManager.h"

GameManager* GameManager::getInstance()
{
    static GameManager instance;
    return &instance;
}

// returns path to the executable
std::string GameManager::getPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

// loads all resources and generaly sets up
void GameManager::init()
{
    try
    {
        // seed random number generator
        srand(static_cast<unsigned int>(time(0)));

        // create the window
        WINDOWMANAGER->createWindow(sf::VideoMode(1280, 720), "Breakout");

        // add Audio
        AUDIOMANAGER->setMusic(getPath() + "\\resources\\audio\\music.ogg");
        AUDIOMANAGER->setBounceSound(getPath() + "\\resources\\audio\\bounce.wav");

#pragma region scary stuff
        scaryTex.loadFromFile(getPath() + "\\resources\\graphics\\scary.jpg");
        scarySprite.setTexture(scaryTex);
        AUDIOMANAGER->setScarySound(getPath() + "\\resources\\audio\\scary.wav");
#pragma endregion

        // initialise text manager
        TEXTMANAGER->init((getPath() + "\\resources\\font\\OCRAEXT.ttf"));

        // set up menu text
        TEXTMANAGER->addText(std::string("Scary Break Out"), 100, sf::Vector2f(100, 0), sf::Color(128, 0, 255));
        TEXTMANAGER->addText(std::string("Play (enter)"), 50, sf::Vector2f(300, 300), sf::Color(128, 0, 255));
        TEXTMANAGER->addText(std::string("Exit (esc)"), 50, sf::Vector2f(300, 400), sf::Color(128, 0, 255));

        // tutorial text
        TEXTMANAGER->addText(std::string("Press Space to serve"), 50, sf::Vector2f(0, 0), sf::Color(128, 0, 255));

        // scary text
        TEXTMANAGER->addText(std::string("I told you it was scary"), 50, sf::Vector2f(0, 0), sf::Color(255, 0, 0));

        // create paddle
        paddle.setSprite(getPath() + "\\resources\\graphics\\paddle.png");
        paddle.getSprite().setPosition(WINDOWMANAGER->getSize().x / 2.0f, WINDOWMANAGER->getSize().y - (paddle.getSprite().getGlobalBounds().height / 2.0f));
        paddle.getSprite().setOrigin(paddle.getSprite().getGlobalBounds().width / 2, paddle.getSprite().getGlobalBounds().height / 2);

        // create ball
        ball.setSprite(getPath() + "\\resources\\graphics\\ball.png");
        ball.getSprite().setOrigin(ball.getSprite().getGlobalBounds().width / 2, ball.getSprite().getGlobalBounds().height / 2);
        //ball.getSprite().setPosition(15, 31);
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

#pragma region update functions

// update while at the menu
void GameManager::updateMenu()
{
    WINDOWMANAGER->getWindow()->draw(*TEXTMANAGER->getText(std::string("Scary Break Out")));
    WINDOWMANAGER->getWindow()->draw(*TEXTMANAGER->getText(std::string("Play (enter)")));
    WINDOWMANAGER->getWindow()->draw(*TEXTMANAGER->getText(std::string("Exit (esc)")));

    if (INPUTMANAGER->mouseButtonPressed(sf::Mouse::Left))
    {
        if (TEXTMANAGER->getText(std::string("Scary Break Out"))->getGlobalBounds().contains(INPUTMANAGER->mousePosition()))
        {
            TEXTMANAGER->getText(std::string("Scary Break Out"))->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }
        if (TEXTMANAGER->getText(std::string("Play (enter)"))->getGlobalBounds().contains(INPUTMANAGER->mousePosition()))
        {
            STATEMANAGER->changeState(STATE::SERVING);
            AUDIOMANAGER->playMusic();
        }
        else if (TEXTMANAGER->getText(std::string("Exit (esc)"))->getGlobalBounds().contains(INPUTMANAGER->mousePosition()))
        {
            WINDOWMANAGER->closeWindow();
        }
    }
    // enter starts the game
    if (INPUTMANAGER->keyPressed(sf::Keyboard::Return))
    {
        STATEMANAGER->changeState(STATE::SERVING);
        AUDIOMANAGER->playMusic();
    }
}

// update while serving
void GameManager::updateServing()
{
    WINDOWMANAGER->getWindow()->draw(*TEXTMANAGER->getText(std::string("Press Space to serve")));
    ball.Serve();
    paddle.Control();
    for (unsigned int i = 0; i < bricks.size(); i++)
    {
        if (bricks[i]->getVisible())
        {
            bricks[i]->draw();
        }
    }
    // check for player's serve
    if(INPUTMANAGER->keyPressed(sf::Keyboard::Key::Space))
    {
        STATEMANAGER->changeState(STATE::PLAYING); // push playing state
    }
}

// update while thye game is paused
void GameManager::updatePaused()
{
    ball.draw();
    paddle.draw();
    for (unsigned int i = 0; i < bricks.size(); i++)
    {
        if (bricks[i]->getVisible())
        {
            bricks[i]->draw();
        }
    }
    // unpause
    if(INPUTMANAGER->keyPressed(sf::Keyboard::Return))
    {
        AUDIOMANAGER->playMusic();
        STATEMANAGER->changeState(STATE::PLAYING);
    }
}

// update while playing the game
void GameManager::updatePlaying()
{
    ball.Move();
    paddle.Control();
    bool hasWon = true;
    for (unsigned int i = 0; i < bricks.size(); i++)
    {
        if (bricks[i]->getVisible())
        {
            hasWon = false;
            bricks[i]->draw();
        }
    }
    // check if player has won
    if (hasWon)
    {
        AUDIOMANAGER->stopMusic(); // stop playing music
        AUDIOMANAGER->playScarySound(); // scary
        STATEMANAGER->changeState(STATE::WON);
    }
    // ball has gone off bottom
    if (ball.getSprite().getPosition().y > WINDOWMANAGER->getSize().y)
    {
        for (unsigned int i = 0; i < bricks.size(); i++)
        {
            bricks[i]->setVisible(true);
        }
        STATEMANAGER->changeState(STATE::SERVING);
    }
    // pause
    if(INPUTMANAGER->keyPressed(sf::Keyboard::Return))
    {
        AUDIOMANAGER->pauseMusic();
        STATEMANAGER->changeState(STATE::PAUSED);
    }
}

// update after the player has won
void GameManager::updateWon()
{
    WINDOWMANAGER->getWindow()->draw(scarySprite);
    WINDOWMANAGER->getWindow()->draw(*TEXTMANAGER->getText(std::string("I told you it was scary")));
    if(INPUTMANAGER->keyPressed(sf::Keyboard::Return))
    {
        for (unsigned int i = 0; i < bricks.size(); i++)
        {
            bricks[i]->setVisible(true);
        }
        STATEMANAGER->changeState(STATE::MENU); // push menu state
    }
}

#pragma endregion