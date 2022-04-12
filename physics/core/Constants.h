#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

constexpr auto DEFAULT_DAMPING_COEFFICIENT = 0.9995f;
constexpr auto GRAVITATIONAL_CONSTANT = 6.674098e-10f;

#include "../math/Vector.h"

namespace Physics{
    namespace Units{
        static float M = 1;
        static float KG = 1;
        static float S = 1;
//        static float MOL = 1;
//        static float AMP = 1;
//        static float K = 1;
//        static float CD = 1;

        static PMath::Vector UP = PMath::init(0, -1, 0);
        static PMath::Vector DOWN = PMath::init(0, 1, 0);
        static PMath::Vector RIGHT = PMath::init(1, 0, 0);
        static PMath::Vector LEFT = PMath::init(-1, 0, 0);
        static PMath::Vector FRONT = PMath::init(0, 0, 1);
        static PMath::Vector BACK = PMath::init(0, 0, -1);
    }
}
#endif // CONSTANTS_H_INCLUDED
