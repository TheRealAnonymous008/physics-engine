#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "../math/Vector.h"

namespace Physics{
    struct Entity {
        PMath::Vector position;
        PMath::Vector velocity;
        PMath::Vector acceleration;
    };
}

#endif // ENTITY_H_INCLUDED
