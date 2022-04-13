#include <SFML/Graphics.hpp>
#include "physics/core/points/Point.h"
#include "physics//core/points/RadialEmitter.h"
#include "physics/core/points/Emitter.h"
#include "physics/core/Engine.h"

#include "physics/render/RenderObjects.h"
#include <iostream>

#include "physics/math/Matrix.h"

#define FRAMERATE_LIMIT 60
using namespace Render;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Physics Engine");
    sf::View view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(500.0f, 500.0f));
    window.setView(view);

    Physics::Engine* engine = new Physics::Engine(1.0f / (3 * FRAMERATE_LIMIT), 1.0f / FRAMERATE_LIMIT);
	// engine->world->ApplyGravity();

	Point* p1 = new Point();
	p1->move(0, 0);
	engine->world->AddEntity(p1);

	Point* p2 = new Point();
	p2->move(100, 0);


	Point* p3 = new Point();
	p3->move(150, 150);
	engine->world->AddEntity(p2);
	engine->world->AddEntity(p3);

	Spring* s1 = new Spring(p2, p1, 1, 150);
	engine->world->AddConstraint(s1);

	Spring* s2 = new Spring(p2, p3, 2, 100);
	engine->world->AddConstraint(s2);

	Spring* s3 = new Spring(p1, p3, 2, 75);
	engine->world->AddConstraint(s2);

    while (window.isOpen())
    {
        window.setFramerateLimit(FRAMERATE_LIMIT);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        engine->Run();

        window.clear();
		
		window.draw(p1->shape);
		window.draw(p2->shape);
		window.draw(p3->shape);
		window.draw(s1->getShape(), 2, sf::Lines);
		window.draw(s2->getShape(), 2, sf::Lines);
		window.draw(s3->getShape(), 2, sf::Lines);

        window.display();

    }

    return 0;
}
