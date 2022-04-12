#ifndef INTEGRATION_H_INCLUDED
#define INTEGRATION_H_INCLUDED

#include "Vector.h"
#include <vector>

namespace PMath {
    // Euler Integration
    const Vector Integrate(const Vector current, float delta, const Vector derivative){
        return current + derivative * delta;
    }

    // Verlet Integration
    std::vector<Vector> Verlet(Vector position, Vector velocity, Vector acceleration, Vector new_acc, float delta){
        PMath::Vector new_pos = position + velocity*delta + acceleration * (delta*delta*0.5f);
        PMath::Vector new_vel = velocity + (acceleration+new_acc) * (delta*0.5f);

        std::vector<Vector> result;
        result.emplace_back(new_pos);
        result.emplace_back(new_vel);
        result.emplace_back(new_acc);

        return result;
    }


    // RK4 Integration
    std::vector<Vector> RungeKutta(Vector position, Vector velocity, Vector acceleration, Vector new_acc, float delta){
        Vector new_pos = position;
        Vector new_vel = velocity;

        Vector k_pos[4], k_vel[4];
        float t_consts[4] = {delta, 1.5f*delta, 1.5f*delta, 2.0f*delta};

        for(int i = 0; i < 4; i++){
            new_pos += new_vel*t_consts[i];
            new_vel += new_acc*t_consts[i];
            k_pos[i] = new_vel;
            k_vel[i] = new_acc;
        }

        // Combined
        Vector dxdt = 1.0f/6.0f * (k_pos[0] + 2.0f * (k_pos[1] + k_pos[2]) + k_pos[3]);
        Vector dvdt = 1.0f/6.0f * (k_vel[0] + 2.0f * (k_vel[1] + k_vel[2]) + k_vel[3]);

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
