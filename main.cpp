#include <SFML/Graphics.hpp>
#include "physics/core/Body.h"
#include "physics/core/Point.h"
#include "physics/core/Engine.h"

struct Ball :public Physics::Point {
    sf::CircleShape shape = sf::CircleShape(5);

    void move(float x, float y){
        this->position = PMath::Vector(x, y);
        shape.setPosition(x, y);
    }

    void on_update() override{
        move(this->position.get_coeff(0), this->position.get_coeff(1));
    }
};

int main()
{
    Ball *b = new Ball();
    Physics::Engine* engine = new Physics::Engine();
    engine->entity_manager->add_entity(b);

    b->move(500, 500);

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Physics Engine");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        engine->run();
        window.clear();
        window.draw(b->shape);
        window.display();
    }

    return 0;
}
