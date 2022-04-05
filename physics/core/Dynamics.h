#ifndef DYNAMICS_H_INCLUDED
#define DYNAMICS_H_INCLUDED

#include "Point.h"
#include "../math/Vector.h"
#include "../math/Integration.h"

namespace Physics{
    inline void ApplyForce(Point* object, const PMath::Vector& force, const float delta){
        // Use F = ma to update the object.
        PMath::Vector acceleration = force / object->mass;
        object->velocity = PMath::Integrate(object->velocity, delta, acceleration);
    }
}

#endif // DYNAMICS_H_INCLUDED
