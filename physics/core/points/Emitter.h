#ifndef EMITTER_H_INCLUDED
#define EMITTER_H_INCLUDED

#include <vector>
#include "../../math/Vector.h"
#include "../Object.h"

namespace Physics{
	// A point mass that emits a certain amount of force in a linear fashion.
    class Emitter : public Point{
    protected:
        PMath::Vector force;
        std::vector<Object*> points = std::vector<Object*>();

    public:
        Emitter(PMath::Vector force = PMath::init(), BodyType type = BodyType::STATIC, int id = 0){
            this->force = force;
            this->type = type;
        }

        virtual void ApplyForce(){
			for (Object* p : points) {
				p->ApplyForce(force);
			}
        }

        void SetForce(PMath::Vector force){
            this->force = force;
        }

        void AddObject(Physics::Object* point){
            if(point != this)
                this->points.push_back(point);
        }

        const PMath::Vector GetForce(){
            return this->force;
        }        
		
		void OnFrameStart(float delta) override{
			ApplyForce();
		}
    };
}

#endif // EMITTER_H_INCLUDED
