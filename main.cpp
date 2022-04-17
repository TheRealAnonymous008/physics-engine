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
	std::vector<DistanceJoint*> joints;

	for (int i = 0; i < 30; i++) {
		Point* p = new Point();
		p->move(i * 15, -100);
		engine->world->AddEntity(p);
		points.push_back(p);
	}

	points[0]->SetType(Physics::BodyType::STATIC);

	for (int i = 0; i < 30; i++) {
		DistanceJoint* h = new DistanceJoint(points[0], points[i]);
		engine->world->AddConstraint(h);
		joints.push_back(h);
	}

	bool applied = false;
    while (window.isOpen())
    {
        window.setFramerateLimit(FRAMERATE_LIMIT);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				engine->world->AddForce(PMath::init(-1000, -1000));
				applied = true;
			}
        }

        engine->Run();

        window.clear();
		
		for (Point* p : points) {
			window.draw(p->shape);
			window.draw(p->GetVelocityVector(), 2, sf::Lines);
		}

		for (DistanceJoint* h : joints) {
			window.draw(h->getShape(), 2, sf::Lines);
		}

        window.display();
		if (applied) {
			engine->world->RemoveForce(PMath::init(-1000, -1000));
			applied = false;
		}

    }

    return 0;
}
