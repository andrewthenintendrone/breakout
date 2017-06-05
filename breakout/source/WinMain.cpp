#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "GameObject.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "breakout");

    GameObject plane(std::string("mouse.png"));
    GameObject x(std::string("x.png"));
    x.transform.translate(window.getSize().x - (x.getSprite().getGlobalBounds().width / 2), x.getSprite().getGlobalBounds().height / 2);
    x.updateTransform();
    plane.transform.translate(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    plane.updateTransform();

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
        sf::FloatRect hitbox = x.getSprite().getGlobalBounds();
        hitbox.left += 20;
        hitbox.height -= 20;
        if (plane.getSprite().getGlobalBounds().intersects(hitbox))
        {
            window.close();
        }
        plane.handleInput(deltaTime.asSeconds());
        window.clear();
        window.draw(x.getSprite());
        window.draw(plane.getSprite());
        window.display();
    }

    return 0;
}