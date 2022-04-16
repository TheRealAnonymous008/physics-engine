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
	
	for (int i = 0; i < 10; i++) {
		Point* p = new Point();
		p->move(i * 20, 0);
		engine->world->AddEntity(p);
		points.push_back(p);
	}

	points[0]->SetType(Physics::BodyType::STATIC);

	Point* p1 = new Point();
	p1->move(200, 20);
	engine->world->AddEntity(p1);

	Point* p2 = new Point();
	p2->move(200, -20);
	engine->world->AddEntity(p2);

	Point* p3 = new Point();
	p3->move(220, 0);
	engine->world->AddEntity(p3);

	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);

	for (int i = 0; i < 9; i++) {
		DistanceJoint* h = new DistanceJoint(points[i], points[i + 1]);
		engine->world->AddConstraint(h);
		joints.push_back(h);
	}

	DistanceJoint* h1 = new DistanceJoint(points[9], p1);
	DistanceJoint* h2 = new DistanceJoint(points[9], p2);
	DistanceJoint* h3 = new DistanceJoint(p1, p3);
	DistanceJoint* h4 = new DistanceJoint(p2, p3);
	DistanceJoint* h5 = new DistanceJoint(p1, p2);

	engine->world->AddConstraint(h1);
	engine->world->AddConstraint(h2);
	engine->world->AddConstraint(h3);
	engine->world->AddConstraint(h4);
	engine->world->AddConstraint(h5);

	joints.push_back(h1);
	joints.push_back(h2);
	joints.push_back(h3);
	joints.push_back(h4);
	joints.push_back(h5);

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

		for (DistanceJoint* h : joints) {
			window.draw(h->getShape(), 2, sf::Lines);
		}

        window.display();

    }

    return 0;
}
