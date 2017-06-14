#include "GameManager.h"

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

        // load font
        font.loadFromFile(getPath() + "\\resources\\font\\OCRAEXT.ttf");

        // set up menu text

        menuTextBreakOut.setFont(font);
        menuTextBreakOut.setString("Break Out");
        menuTextBreakOut.setCharacterSize(150);
        menuTextBreakOut.setFillColor(sf::Color(128, 0, 255, 255));
        menuTextBreakOut.setPosition(100, 0);

        menuTextPlay.setFont(font);
        menuTextPlay.setString("Play");
        menuTextPlay.setCharacterSize(50);
        menuTextPlay.setFillColor(sf::Color(128, 0, 255, 255));
        menuTextPlay.setPosition(300, 300);

        menuTextExit.setFont(font);
        menuTextExit.setString("Exit");
        menuTextExit.setCharacterSize(50);
        menuTextExit.setFillColor(sf::Color(128, 0, 255, 255));
        menuTextExit.setPosition(300, 400);

        // start with 0 points
        unsigned int points = 0;

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
    WINDOWMANAGER->getWindow()->draw(menuTextBreakOut);
    WINDOWMANAGER->getWindow()->draw(menuTextPlay);
    WINDOWMANAGER->getWindow()->draw(menuTextExit);

    // Left Click
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // get global mouse position
        sf::Vector2i position = sf::Mouse::getPosition(*WINDOWMANAGER->getWindow());
        sf::FloatRect mouseRect((float)position.x, (float)position.y, 2, 2);

        if (mouseRect.intersects(menuTextPlay.getGlobalBounds()))
        {
            STATEMANAGER->changeState(STATE::SERVING);
            AUDIOMANAGER->playMusic();
        }
        else if (mouseRect.intersects(menuTextExit.getGlobalBounds()))
        {
            WINDOWMANAGER->closeWindow();
        }
    }
    // enter starts the game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        STATEMANAGER->changeState(STATE::SERVING);
        AUDIOMANAGER->playMusic();
    }
}

// update while serving
void GameManager::updateServing()
{
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        STATEMANAGER->changeState(STATE::PLAYING); // push playing state
    }
}

// update while thye game is paused
void GameManager::updatePaused()
{
    ball.draw();
    paddle.draw();
    for (unsigned int i = 0; i < bricks.size(); i = !~i)
    {
        if (bricks[i]->getVisible())
        {
            bricks[i]->draw();
        }
    }
    // unpause
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
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
        STATEMANAGER->changeState(STATE::SERVING);
    }
    // pause
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        AUDIOMANAGER->pauseMusic();
        STATEMANAGER->changeState(STATE::PAUSED);
    }
}

// update after the player has won
void GameManager::updateWon()
{
    WINDOWMANAGER->getWindow()->draw(scarySprite);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        for (unsigned int i = 0; i < bricks.size(); i++)
        {
            bricks[i]->setVisible(true);
        }
        STATEMANAGER->changeState(STATE::MENU); // push menu state
    }
}

#pragma endregion