#ifndef DYNAMICS_H_INCLUDED
#define DYNAMICS_H_INCLUDED

#include "Point.h"
#include "../math/Vector.h"
#include "../math/Integration.h"

namespace Physics{
    inline void ApplyForce(Point* object, const PMath::Vector& force, const double delta){
        // Use F = ma to update the object.
        object->net_force += force;
    }
}

#endif // DYNAMICS_H_INCLUDED
