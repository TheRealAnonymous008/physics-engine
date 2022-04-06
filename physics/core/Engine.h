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
                std::chrono::_V2::high_resolution_clock::time_point start_time;
                std::chrono::_V2::high_resolution_clock::time_point last_cycle_time;
                int ticked = 0;

            public:
                Clock() {
                }

                const double GetDelta(){
                    auto end_time = std::chrono::_V2::high_resolution_clock::now();
                    double delta = ticked * std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - last_cycle_time).count() / 1000000000.0f;
                    last_cycle_time = end_time;
                    ticked = 1;

                    return delta;
                }

                void Start(){
                    start_time = std::chrono::_V2::high_resolution_clock::now();
                    ticked = 0;
                }
        };
    }

    class Engine{
        private:
            double time_resolution;
            double accumulator = 0;
            double display_rate;

        public:
            Internal::EntityManager* entity_manager;
            Internal::Clock* clock;

            Engine(const double time_resolution = 1.0/120.0, const double display_rate = 1.0/60.0){
                this->time_resolution = time_resolution;
                this->display_rate = display_rate;
                entity_manager = new Internal::EntityManager();
                clock = new Internal::Clock();
            }

            void Run(){
                double delta = clock->GetDelta();
                double frame_rate = std::min(delta, display_rate);

                accumulator += frame_rate;
                if (delta == 0)
                    return;

                while(accumulator >= time_resolution){
                    for (Point* entity : *entity_manager->GetEntitites()){
                        // Perform updates to entity objects here.

                        PMath::Vector f = PMath::Vector(-entity->position.get(1), entity->position.get(0));
                        entity->velocity = f;
                        entity->Update(time_resolution);
                    }
                    accumulator -= time_resolution;
                }

                for (Point* entity : *entity_manager->GetEntitites()) {
                    entity->Interpolate(accumulator / time_resolution);
                }

            }

            void ThreadedRun(std::future<void> exit_signal, int wait_microseconds = 0){
                while(exit_signal.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout){
                    Run();
                }
            }

    };


}


#endif // ENGINE_H_INCLUDED
