#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

#include <chrono>

namespace Physics{
    namespace Internal{
        class Clock{
            private:
                std::chrono::high_resolution_clock::time_point start_time;
                std::chrono::high_resolution_clock::time_point last_cycle_time;
                int ticked = 0;

            public:
                Clock() {
                }

                const float GetDelta(){
                    auto end_time = std::chrono::high_resolution_clock::now();
                    float delta = ticked * std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - last_cycle_time).count() / 1000000000.0f;
                    last_cycle_time = end_time;
                    ticked = 1;

                    return delta;
                }

                void Start(){
                    start_time = std::chrono::high_resolution_clock::now();
                    ticked = 0;
                }
        };
    }
}

#endif // CLOCK_H_INCLUDED
