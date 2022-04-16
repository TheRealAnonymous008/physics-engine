#ifndef HINGEJOINT_H_INCLUDED
#define HINGEJOINT_H_INCLUDED

#include "JointConstraint.h"
#include "../../math/Vector.h"
#include <iostream>

namespace Physics {
	class HingeJoint : public JointConstraint {
	protected:
		float half_norm;

	public:
		HingeJoint(Object* first, Object* second) {
			this->first = first;
			this->second = second;
			this->half_norm = PMath::norm(first->transform.position - second->transform.position) / 2.0f;
		}
		
		// Constraint: The length must stay fixed, but rotation about the first object is allowed about a specified axis.
		void ApplyConstraint(float delta) override {
			const PMath::Vector midpoint = PMath::midpoint(first->transform.position, second->transform.position);
			const PMath::Vector dir = PMath::normalize(first->transform.position - second->transform.position);

			if (first->GetType() != BodyType::STATIC) {
				first->transform.position = midpoint + dir * half_norm;
			}

			if (second->GetType() != BodyType::STATIC) {
				second->transform.position = midpoint - dir * half_norm;
			}
		}
	};
}


#endif