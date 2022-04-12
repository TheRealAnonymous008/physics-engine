#ifndef RADIALEMITTER_H_INCLUDED
#define RADIALEMITTER_H_INCLUDED

#include "Emitter.h"
#include "../../math/Vector.h"

namespace Physics {
	class RadialEmitter : public Emitter{
	private:
		float radius;
		float degree;

	public:
		RadialEmitter(PMath::Vector force, float radius, float degree = 2.0f, BodyType type = BodyType::DYNAMIC) {
			this->force = force;
			this->type = type;
			this->radius = radius;
			this->degree = degree;
		}

		void ApplyForce(){
			for (Object* p : points) {
				float radius = PMath::norm(p->transform.position - this->transform.position);
				PMath::Vector applied = force / pow(radius, degree);
				p->ApplyForce(force);
			}
		}
	};
}


#endif
