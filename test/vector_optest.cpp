#include "../physics/math/Vector.h"
#include <bits/stdc++.h>
#include <assert.h>

#define TOLERANCE 1e-17

int main(){
    PMath::Vector v1(1, 2, 3, 4);
    PMath::Vector v2(2, -1, 0.1);

    assert(v1 + v2 == PMath::Vector(3, 1, 3.1, 4));
    assert(v1 - v2 == PMath::Vector(-1, 3, 2.9, 4));
    assert((3.0 * v2)== PMath::Vector(6, -3, 0.3, 0));
    assert((v1 / 2)== PMath::Vector(0.5, 1, 1.5, 2));
    assert(v1.dot(v2) - 4.0f/3.0f < TOLERANCE);

    v1 *= 2;
    assert(v1 == PMath::Vector(2, 4, 6, 8));

    v2 = -v1;
    assert(v2 == PMath::Vector(-2, -4, -6, -8));

    v1.normalize();
    assert(v1.norm() -1 <= TOLERANCE);

    std::cout<<"Test Successful";
    return 0;
}
