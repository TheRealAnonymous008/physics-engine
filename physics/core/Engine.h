#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <bits/stdc++.h>
#include "points/Point.h"
#include "Dynamics.h"
#include "Internal.h"
#include "Clock.h"

#include "Constants.h"

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
    }

    class Engine{
        private:
            double time_resolution;
            double accumulator = 0;
            double display_rate;

        public:
            Internal::EntityManager* entity_manager = new Internal::EntityManager();
            Internal::Clock* clock = new Internal::Clock();

            Engine(const double time_resolution = 1.0/120.0, const double display_rate = 1.0/60.0){
                this->time_resolution = time_resolution;
                this->display_rate = display_rate;
            }

            void Run(){
                using namespace Physics::Units;
                double delta = clock->GetDelta();
                double frame_rate = std::min(delta, display_rate) * S;

                std::vector<Point*> entities = *entity_manager->GetEntitites();

                accumulator += frame_rate;
                if (delta == 0)
                    return;

                while(accumulator >= time_resolution){
                    for (Point* entity : entities){
                        // Perform updates to entity objects here.

                        PMath::Vector f = PMath::Vector(-entity->GetPosition().get(1), entity->GetPosition().get(0));
                        entity->SetVelocity(f);
                        entity->Update(time_resolution);
                    }
                    accumulator -= time_resolution;
                }

                for (Point* entity : entities) {
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
