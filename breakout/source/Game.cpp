#include "Game.h"

Game* Game::getInstance()
{
    static Game game;
    return &game;
}

// returns path to the executable
std::string Game::getPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

void Game::init()
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
        // move this
        AUDIOMANAGER->playMusic();

        // load font
        font.loadFromFile(getPath() + "\\resources\\font\\OCRAEXT.ttf");

        // set up menu text

        menuTextBreakOut.setFont(font);
        menuTextBreakOut.setString("Break Out");
        menuTextBreakOut.setCharacterSize(150);
        menuTextBreakOut.setFillColor(sf::Color(128, 0, 255, 255));
        menuTextBreakOut.move(100, 0);

        menuTextPlay.setFont(font);
        menuTextPlay.setString("Play");
        menuTextPlay.setCharacterSize(50);
        menuTextPlay.setFillColor(sf::Color(128, 0, 255, 255));
        menuTextPlay.move(300, 300);

        menuTextExit.setFont(font);
        menuTextExit.setString("Exit");
        menuTextExit.setCharacterSize(50);
        menuTextExit.setFillColor(sf::Color(128, 0, 255, 255));
        menuTextExit.move(300, 400);

        // start with 0 points
        unsigned int points = 0;

        // create paddle
        paddle.setSprite(getPath() + "\\resources\\graphics\\paddle.png");
        paddle.getSprite().move(WINDOWMANAGER->getSize().x / 2.0f, WINDOWMANAGER->getSize().y - (paddle.getSprite().getGlobalBounds().height / 2.0f));

        // create ball
        ball.setSprite(getPath() + "\\resources\\graphics\\ball.png");
        ball.getSprite().setOrigin(ball.getSprite().getScale().x / 2, ball.getSprite().getScale().y / 2);
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

void Game::UpdateMenu()
{
    WINDOWMANAGER->getWindow()->draw(menuTextBreakOut);
    WINDOWMANAGER->getWindow()->draw(menuTextPlay);
    WINDOWMANAGER->getWindow()->draw(menuTextExit);

    // Left Click
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // get global mouse position
        sf::Vector2i position = sf::Mouse::getPosition(*WINDOWMANAGER->getWindow());
        sf::FloatRect mouseRect(position.x, position.y, 2, 2);

        if (mouseRect.intersects(menuTextPlay.getGlobalBounds()))
        {
            GAMESTATEMANAGER->popState(); // pop menu state
            GAMESTATEMANAGER->pushState(GAMESTATE::PLAYING);
        }
        else if (mouseRect.intersects(menuTextExit.getGlobalBounds()))
        {
            WINDOWMANAGER->closeWindow();
        }
    }
}

void Game::UpdateServing()
{

}

void Game::UpdatePlaying()
{
    ball.Move();
    paddle.Control();
    for (unsigned int i = 0; i < bricks.size(); i++)
    {
        if (bricks[i]->getVisible())
        {
            bricks[i]->draw();
        }
    }
}

void Game::UpdatePaused()
{

}

void Game::UpdateWon()
{

}