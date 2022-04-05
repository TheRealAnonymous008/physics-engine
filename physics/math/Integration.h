#ifndef INTEGRATION_H_INCLUDED
#define INTEGRATION_H_INCLUDED

#include "Vector.h"

namespace PMath {
    // Euler Integration
    double Integrate(double current, double delta, double derivative){
        return current + derivative * delta;
    }

    const Vector Integrate(const Vector current, double delta, const Vector derivative){
        return current + delta * derivative;
    }
}

#endif // INTEGRATION_H_INCLUDED
