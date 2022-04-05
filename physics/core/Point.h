#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "../math/Vector.h"

namespace Physics{
    struct Point {
        PMath::Vector position;
        PMath::Vector rotation;
        double mass = 1;

        virtual ~Point(){

        }

        void update(PMath::Vector delta_position){
            this->position += delta_position;
            on_update();
        }

        virtual void on_update(){

        }
    };


}

#endif // POINT_H_INCLUDED
