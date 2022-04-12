#include <SFML/Graphics.hpp>
#include "physics/core/points/Point.h"
#include "physics//core/points/RadialEmitter.h"
#include "physics/core/points/Emitter.h"
#include "physics/core/Engine.h"

#include "physics/render/RenderObjects.h"
#include <iostream>


#define FRAMERATE_LIMIT 60
using namespace Render;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Physics Engine");
    sf::View view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(500.0f, 500.0f));
    window.setView(view);

    Physics::Engine* engine = new Physics::Engine(1.0f / (3 * FRAMERATE_LIMIT), 1.0f / FRAMERATE_LIMIT);
	//engine->world->ApplyGravity();

	RadialEmitter* sample = new RadialEmitter();
	sample->move(-240, 0);
	sample->SetForce(100);
	engine->world->AddEntity(sample);

    std::vector<Point*> balls = std::vector<Point*>();

    for (int i = -10; i <= 10; i++){
        for (int j = -10; j <= 10; j++){
			Point* b = new Point();
			engine->world->AddEntity(b);
            b->move(i * 10.0f , j * 10.0f);
            balls.push_back(b);
			sample->AddObject(b);
        }
    }
	
    /*for(Ball* b : balls){
        for(Ball* c : balls){
            b->AddPoint(c);
        }
    }
*/
//    Ball *b = new Ball();
//    engine->entity_manager->AddEntity(b);
//    b->move(0, 100);
//    balls.push_back(b);

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
		window.draw(sample->shape);
        for (Point* b : balls){
            window.draw(b->shape);
        }

        window.display();

    }

    return 0;
}
