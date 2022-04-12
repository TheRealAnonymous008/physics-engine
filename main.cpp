#include <SFML/Graphics.hpp>
#include "physics/core/points/Point.h"
#include "physics/core/points/Emitter.h"
#include "physics/core/Engine.h"

#include <iostream>


#define FRAMERATE_LIMIT 60


class Ball : public Physics::Point {
    private:
        void OnUpdate() override{
            //Physics::Emitter::OnUpdate();
            move(this->position.vec[0], this->position.vec[1]);
        }
		
    public:
        sf::CircleShape shape = sf::CircleShape(5);

        void move(float x, float y){
            this->position = (PMath::init(x, y));
            float r_x = GetScaledPosition().vec[0];
            float r_y = GetScaledPosition().vec[1];
            shape.setPosition(r_x, r_y);
        }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Physics Engine");
    sf::View view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(500.0f, 500.0f));
    window.setView(view);

    Physics::Engine* engine = new Physics::Engine(1.0f / (2 * FRAMERATE_LIMIT), 1.0f / FRAMERATE_LIMIT);

    std::vector<Ball*> balls = std::vector<Ball*>();

    for (int i = -15; i <= 15; i++){
        for (int j = -10; j <= 10; j++){
			Ball* b = new Ball();
            engine->entity_manager->AddEntity(b);
            b->move(i * 10.0f, j * 10.0f);
            balls.push_back(b);
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
        for (Ball* b : balls){
            window.draw(b->shape);
        }

        window.display();

    }

    return 0;
}
