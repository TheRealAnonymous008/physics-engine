#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "../math/Vector.h"
#include "../math/Integration.h"

namespace Physics{

    enum BodyType{
        STATIC,
        KINEMATIC,
        DYNAMIC
    };

    class Point {
        private:
            BodyType type;

            PMath::Vector old_position;
            PMath::Vector old_velocity;
            PMath::Vector old_acceleration;

        public:

            PMath::Vector position;
            PMath::Vector velocity;
            PMath::Vector acceleration;

            PMath::Vector rotation;


            PMath::Vector net_force;
            double mass = 1;

            Point(BodyType type = BodyType::KINEMATIC){
                this->type = type;
            }

            virtual ~Point(){

            }

            void Update(double delta){

                old_position = position;
                old_velocity = velocity;
                old_acceleration = acceleration;

                std::vector<PMath::Vector> result = PMath::Verlet(position, velocity, acceleration, net_force / mass, delta);

                if (type == BodyType::DYNAMIC){
                    acceleration = result[2];
                    velocity = result[1];
                }
                if (type != BodyType::STATIC){
                    position = result[0];
                }

                OnUpdate();
                net_force = PMath::Vector();
            }

            virtual void OnUpdate(){

            }
    };


}

#endif // POINT_H_INCLUDED
