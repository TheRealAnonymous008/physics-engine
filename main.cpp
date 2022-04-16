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
	engine->world->ApplyGravity();

	std::vector<Point*> points;
	std::vector<HingeJoint*> joints;
	
	for (int i = 0; i < 10; i++) {
		Point* p = new Point;
		p->move(i * 10, 0);
		engine->world->AddEntity(p);
		points.push_back(p);
	}

	points[0]->SetType(Physics::BodyType::STATIC);
	points[9]->SetMass(100);

	for (int i = 0; i < 9; i++) {
		HingeJoint* h = new HingeJoint(points[i], points[i + 1]);
		engine->world->AddConstraint(h);
		joints.push_back(h);
	}

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
		
		for (Point* p : points) {
			window.draw(p->shape);
		}

		for (HingeJoint* h : joints) {
			window.draw(h->getShape(), 2, sf::Lines);
		}

        window.display();

    }

    return 0;
}
