#ifndef INTERNAL_H_INCLUDED
#define INTERNAL_H_INCLUDED



namespace Physics{
    namespace Internal{
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

        namespace Constants{
            static double M = 2;
            static double KG = 1;
            static double S = 1;
//            static double MOL = 1;
//            static double AMP = 1;
//            static double K = 1;
//            static double CD = 1;
        };
    }
}

#endif // INTERNAL_H_INCLUDED
