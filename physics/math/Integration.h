#ifndef INTEGRATION_H_INCLUDED
#define INTEGRATION_H_INCLUDED

#include "Vector.h"
#include <bits/stdc++.h>

namespace PMath {
    // Euler Integration
    const Vector Integrate(const Vector current, double delta, const Vector derivative){
        return current + delta * derivative;
    }

    // Verlet Integration
    std::vector<Vector> Verlet(Vector position, Vector velocity, Vector acceleration, Vector new_acc, double delta){
        PMath::Vector new_pos = position + delta*velocity + (delta*delta*0.5)*acceleration;
        PMath::Vector new_vel = velocity + (delta*0.5)*(acceleration+new_acc);

        std::vector<Vector> result;
        result.push_back(new_pos);
        result.push_back(new_vel);
        result.push_back(new_acc);

        return result;
    }


    // RK4 Integration
    std::vector<Vector> RungeKutta(Vector position, Vector velocity, Vector acceleration, Vector new_acc, double delta){
        Vector new_pos = position;
        Vector new_vel = velocity;

        Vector k_pos[4], k_vel[4];
        double t_consts[4] = {delta, 1.5*delta, 1.5*delta, 2.0*delta};

        for(int i = 0; i < 4; i++){
            new_pos += t_consts[i]*new_vel;
            new_vel += t_consts[i]*new_acc;
            k_pos[i] = new_vel;
            k_vel[i] = new_acc;
        }

        // Combined
        Vector dxdt = 1.0/6.0 * (k_pos[0] + 2.0 * (k_pos[1] + k_pos[2]) + k_pos[3]);
        Vector dvdt = 1.0/6.0 * (k_vel[0] + 2.0 * (k_vel[1] + k_vel[2]) + k_vel[3]);

        new_pos += delta*dxdt;
        new_vel += delta*dvdt;

        std::vector<Vector> result;
        result.push_back(new_pos);
        result.push_back(new_vel);
        result.push_back(new_acc);
        return result;
    }
}

#endif // INTEGRATION_H_INCLUDED
