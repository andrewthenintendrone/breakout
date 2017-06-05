#include <Windows.h>
#include <SFML\Graphics.hpp>
#include "GameObject.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "breakout");

    GameObject testObject;
    testObject.setSprite(std::string("ship.png"));
    testObject.transform.translate(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    sf::Clock clock;
    sf::Time deltaTime;

    while (window.isOpen())
    {
        deltaTime = clock.getElapsedTime();
        clock.restart();

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

        testObject.handleInput(deltaTime.asSeconds());

        window.clear();
        window.draw(testObject.getSprite());
        window.display();
    }

    return 0;
}