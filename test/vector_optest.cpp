#include "../physics/math/Vector.h"
#include <bits/stdc++.h>
#include <assert.h>

#define TOLERANCE 1e-17

int foo(){
    PMath::Vector v1 = PMath::init(1.0, 2.0, 3.0, 4.0);
    PMath::Vector v2 = PMath::init(2, -1, 0.1);

    assert(v1 + v2 == PMath::init(3, 1, 3.1, 4));
    assert(v1 - v2 == PMath::init(-1, 3, 2.9, 4));
    assert((v2 * 3.0)== PMath::init(6, -3, 0.3, 0));
    assert((v1 / 2)== PMath::init(0.5, 1, 1.5, 2));
    assert(dot(v1, v2) - 4.0f/3.0f < TOLERANCE);

    v1 *= 2;
    assert(v1 == PMath::init(2, 4, 6, 8));

    v2 = -v1;
    assert(v2 == PMath::init(-2, -4, -6, -8));

    normalize(v1);
    assert(norm(v1) -1 <= TOLERANCE);

    std::cout<<"Test Successful";
    return 0;
}
