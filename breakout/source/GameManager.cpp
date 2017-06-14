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
            STATEMANAGER->popState(); // pop menu state
            STATEMANAGER->pushState(STATE::SERVING);
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
        STATEMANAGER->popState(); // pop menu state
        STATEMANAGER->pushState(STATE::SERVING); // push serving state
        AUDIOMANAGER->playMusic();
    }
}

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
        STATEMANAGER->popState(); // pop serving state
        STATEMANAGER->pushState(STATE::PLAYING); // push playing state
    }
}

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
        AUDIOMANAGER->stopMusic();
        AUDIOMANAGER->playScarySound(); // scary
        STATEMANAGER->popState(); // pop playing state
        STATEMANAGER->pushState(STATE::WON); // push won state
    }
    // ball has gone off bottom
    if (ball.getSprite().getPosition().y > WINDOWMANAGER->getSize().y)
    {
        STATEMANAGER->popState(); // pop playing state
        STATEMANAGER->pushState(STATE::SERVING); // push serving state
    }
}

void GameManager::updatePaused()
{

}

void GameManager::updateWon()
{
    WINDOWMANAGER->getWindow()->draw(scarySprite);
}
#pragma endregion