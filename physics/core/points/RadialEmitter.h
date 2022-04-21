#ifndef RADIALEMITTER_H_INCLUDED
#define RADIALEMITTER_H_INCLUDED

#include "Emitter.h"
#include "../../math/Vector.h"


#include <iostream>

namespace Physics {

	using namespace Physics::Units;
	// A point mass that emits a force radially. Force is applied proportional to the distance to the emitter.
	// For composite objects, the force is applied on each vertex.
	class RadialEmitter : public Emitter{
	private:
		float radius;
		float degree;
		float force;

	public:
		RadialEmitter(float force = 0.0f, float radius = 1.0f, float degree = 2.0f, BodyType type = BodyType::STATIC, int id = 0) {
			this->force = force;
			this->type = type;
			this->radius = radius;
			this->degree = degree;
		}

		void ApplyForce() override{
			for (Object* pt : points) { 
				for (Object* p : pt->GetPrimitives()) {
					PMath::Vector vec = p->transform.position - this->transform.position;
					float r = PMath::norm(vec) + DEFAULT_SMOOTHING_COEFFICIENT * M;
					PMath::Vector applied = force * (vec / pow(r, degree));
					p->ApplyForce(applied);
				}
			}
		}

		void SetForce(PMath::Vector force) = delete;
		void SetForce(float force) {
			this->force = force;
		}
	};
}


#endif
