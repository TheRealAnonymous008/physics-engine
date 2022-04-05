#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "../math/Vector.h"

namespace Physics{
    struct Point {
        PMath::Vector position;
        PMath::Vector rotation;
        double mass = 1;
    };


}

#endif // POINT_H_INCLUDED
