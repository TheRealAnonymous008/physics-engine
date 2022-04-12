#ifndef EMITTER_H_INCLUDED
#define EMITTER_H_INCLUDED

#include <vector>
#include "../../math/Vector.h"
#include "Point.h"
#include "../Object.h"

namespace Physics{
    class Emitter : public Point{
    protected:
        PMath::Vector force;
        std::vector<Point*> points = std::vector<Point*>();

    public:
        Emitter(PMath::Vector force = PMath::init(1,0), BodyType type = BodyType::DYNAMIC){
            this->force = force;
            this->type = type;
        }

        void ApplyForce(){
            for(Point* p : points){
                p->ApplyForce(force);
            }
        }

        void SetForce(PMath::Vector force){
            this->force = force;
        }

        void AddPoint(Physics::Point* point){
            if(point != this)
                this->points.push_back(point);
        }

        const PMath::Vector GetForce(){
            return this->force;
        }        
		
		void OnFrameStart() {
			ApplyForce();
		}
    };
}

#endif // EMITTER_H_INCLUDED
