#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <bits/stdc++.h>
#include "Point.h"
#include "Dynamics.h"

namespace Physics{
    namespace Internal{
        class EntityManager{
            private:
                std::vector<Point*> entities;

            public:
                EntityManager(){
                    entities = std::vector<Point*>();
                }

                void AddEntity(Point* p){
                    this->entities.push_back(p);
                }

                const std::vector<Point*>* GetEntitites() const{
                    return &this->entities;
                }

        };

        class Clock{
            private:
                std::chrono::_V2::steady_clock::time_point start_time;
                std::chrono::_V2::steady_clock::time_point last_cycle_time;
                int ticked = 0;

            public:
                Clock() {
                }

                const double GetDelta(){
                    auto end_time = std::chrono::_V2::steady_clock::now();
                    double delta = ticked * std::chrono::duration_cast<std::chrono::milliseconds>(end_time - last_cycle_time).count() / 1000.0f;
                    last_cycle_time = end_time;
                    ticked = 1;

                    return delta;
                }

                void Start(){
                    start_time = std::chrono::_V2::steady_clock::now();
                    ticked = 0;
                }
        };
    }

    class Engine{
        private:
            float time_resolution;
            double cumulative_time = 0.0f;

        public:
            Internal::EntityManager* entity_manager;
            Internal::Clock* clock;

            Engine(const float time_resolution = 1.0/60.0){
                this->time_resolution = time_resolution;
                entity_manager = new Internal::EntityManager();
                clock = new Internal::Clock();
            }

            void Run(){
                double delta = clock->GetDelta();

                for (Point* entity : *entity_manager->GetEntitites()){
                    // Perform updates to entity objects here.
                    ApplyForce(entity, PMath::Vector(100.0f), delta);
                    entity->Update(delta);
                }

                this->cumulative_time += delta;
            }

    };


}


#endif // ENGINE_H_INCLUDED
