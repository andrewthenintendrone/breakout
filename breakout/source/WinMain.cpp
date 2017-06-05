#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "breakout");
    GameObject testObject;
    testObject.setSprite(std::string("ship.png"));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(testObject.getSprite());
        window.display();
    }

    return 0;
}