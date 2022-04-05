#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "../math/Vector.h"

namespace Physics{
    struct Point {
        PMath::Vector position;
        PMath::Vector velocity;    // Keep track of velocity for Inertial Frame of Reference.

        PMath::Vector rotation;
        double mass = 1;

        virtual ~Point(){

        }

        void Update(double delta){
            this->position += delta * velocity;
            OnUpdate();
        }

        virtual void OnUpdate(){

        }
    };


}

#endif // POINT_H_INCLUDED
