#include <SFML/Graphics.hpp>
#include "physics/core/Body.h"
#include "physics/core/Point.h"
#include "physics/core/Engine.h"

#include <bits/stdc++.h>

#define FRAMERATE_LIMIT 60


struct Ball :public Physics::Point {
    sf::CircleShape shape = sf::CircleShape(5);

    void move(double x, double y){
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

    sf::View view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(500.0f, 500.0f));
    window.setView(view);

    Physics::Engine* engine = new Physics::Engine(1.0f / (4 * FRAMERATE_LIMIT));

    std::vector<Ball*> balls = std::vector<Ball*>();

    for (int i = -50; i < 50; i++){
        for (int j = -50; j < 50; j++){
            Ball *b = new Ball();
            engine->entity_manager->AddEntity(b);
            b->move(i * 10, j * 10);
            b->move(i * 10, j * 10);
            balls.push_back(b);
        }
    }

    std::promise<void> exit_signal;

    std::thread physics_thread(Physics::Engine::ThreadedRun, engine, std::move(exit_signal.get_future()));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (Ball* b : balls)
            window.draw(b->shape);
        window.display();

    }

    exit_signal.set_value();
    physics_thread.join();

    return 0;
}
