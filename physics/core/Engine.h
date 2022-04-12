#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <vector>
#include <future>

#include "points/Point.h"
#include "points/Emitter.h"
#include "Dynamics.h"
#include "Internal.h"
#include "Clock.h"

#include "Constants.h"
#include <cmath>


namespace Physics{
    namespace Internal{
        class EntityManager{
        private:
            std::vector<Point*> entities;
            std::vector<Emitter*> emitters;

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
        float time_resolution;
		float accumulator = 0;
		float display_rate;
		float cumulative = 0;

    public:
        Internal::EntityManager* entity_manager = new Internal::EntityManager();
        Internal::Clock* clock = new Internal::Clock();

        Engine(const float time_resolution = 1.0/120.0, const float display_rate = 1.0/60.0){
            this->time_resolution = time_resolution;
            this->display_rate = display_rate;
        }

        void Run(){
            using namespace Physics::Units;
            float delta = clock->GetDelta();
            float frame_rate = fmin(delta, display_rate) * S;
				
            std::vector<Point*> entities = *entity_manager->GetEntitites();

            accumulator += frame_rate;
            cumulative += frame_rate;

            if (delta == 0)
                return;

            while(accumulator >= time_resolution){
                for (Point* entity : entities){
                    // Perform updates to entity objects here.

                    PMath::Vector f = PMath::init(-entity->GetPosition().vec[1], entity->GetPosition().vec[0]);
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

        double GetCumulative(){
            return cumulative;
        }

    };


}


#endif // ENGINE_H_INCLUDED
