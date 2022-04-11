#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define DEFAULT_DAMPING_COEFFICIENT 0.9995
#define GRAVITATIONAL_CONSTANT 6.674098e-10

#include "../math/Vector.h"

namespace Physics{
    namespace Units{
        static double M = 2;
        static double KG = 1;
        static double S = 1;
//        static double MOL = 1;
//        static double AMP = 1;
//        static double K = 1;
//        static double CD = 1;

        static PMath::Vector UP = PMath::init(0, 1, 0);
        static PMath::Vector DOWN = PMath::init(0, -1, 0);
        static PMath::Vector RIGHT = PMath::init(1, 0, 0);
        static PMath::Vector LEFT = PMath::init(-1, 0, 0);
        static PMath::Vector FRONT = PMath::init(0, 0, 1);
        static PMath::Vector BACK = PMath::init(0, 0, -1);
    }
}
#endif // CONSTANTS_H_INCLUDED
