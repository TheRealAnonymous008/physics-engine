#include <SFML/Graphics.hpp>
#include "physics/core/Body.h"
#include "physics/core/Point.h"
#include "physics/core/Engine.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Physics Engine");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.display();
    }

    return 0;
}
