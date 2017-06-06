#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "TimeManager.h"
#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"

// returns path to the executable
std::string getPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "breakout");

    // font
    sf::Font font;
    font.loadFromFile(getPath() + "\\resources\\OCRAEXT.ttf");

    // text
    sf::Text text;
    text.setFont(font);
    text.setString("it was never seen again...");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color(128, 0, 255, 255));

    // points
    unsigned int points = 1;

    Paddle paddle(getPath() + "\\resources\\paddle.png");
    paddle.transform.translate(window.getSize().x / 2.0f, window.getSize().y - (paddle.getSprite().getGlobalBounds().height / 2.0f));

    Ball ball(getPath() + "\\resources\\ball.png");
    ball.transform.translate(200, 300);
    ball.setPaddle(&paddle);

    sf::Clock clock;
    sf::Time deltaTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        TIME->Update();
        paddle.Update(&window);
        ball.Update(&window);
        window.clear();
        if (ball.getSprite().getGlobalBounds().top >= 720)
        {
            window.draw(text);
        }
        window.draw(paddle.getSprite());
        window.draw(ball.getSprite());
        window.display();
    }

    return 0;
}