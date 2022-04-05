#include <SFML/Graphics.hpp>
#include "physics/core/Body.h"
#include "physics/core/Point.h"
#include "physics/core/Engine.h"

#define FRAMERATE_LIMIT 60

struct Ball :public Physics::Point {
    sf::CircleShape shape = sf::CircleShape(5);

    void move(float x, float y){
        this->position = PMath::Vector(x, y);
        shape.setPosition(x, y);
    }

    void OnUpdate() override{
        move(this->position.get(0), this->position.get(1));
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Physics Engine");
    window.setFramerateLimit(FRAMERATE_LIMIT);

    Ball *b = new Ball();
    Physics::Engine* engine = new Physics::Engine(1.0f / FRAMERATE_LIMIT);
    engine->entity_manager->AddEntity(b);

    b->move(500, 500);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        engine->Run();
        window.clear();
        window.draw(b->shape);
        window.display();
    }

    return 0;
}
