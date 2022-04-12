#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <vector>
#include <future>

#include "Object.h"
#include "Clock.h"
#include "World.h"

#include "Constants.h"
#include <cmath>


namespace Physics{
    class Engine{
    private:
        float time_resolution;
		float accumulator = 0;
		float display_rate;
		float cumulative = 0;

    public:
        World* world = new World();
        Internal::Clock* clock = new Internal::Clock();

        Engine(const float time_resolution = 1.0/120.0, const float display_rate = 1.0/60.0){
            this->time_resolution = time_resolution;
            this->display_rate = display_rate;
        }

        void Run(){
            using namespace Physics::Units;
            float delta = clock->GetDelta();
            float frame_rate = fmin(delta, display_rate) * S;
				
            std::vector<Object*> entities = world->GetEntitites();

            accumulator += frame_rate;
            cumulative += frame_rate;

            if (delta == 0)
                return;

			for (Object* entity : entities) {
				entity->OnFrameStart(accumulator / time_resolution);
			}

            while(accumulator >= time_resolution){
                for (Object* entity : entities){
                    // Perform updates to entity objects here.

                    PMath::Vector f = PMath::init(-entity->transform.position.vec[1], entity->transform.position.vec[0]);
                    entity->transform.velocity = f;
                    entity->Update(time_resolution);
                }
                accumulator -= time_resolution;
            }

            for (Object* entity : entities) {
                entity->OnFrameEnd(accumulator / time_resolution);
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
