#ifndef DISTANCEJOINT_H_INCLUDED
#define DISTANCEJOINT_H_INCLUDED

#include "JointConstraint.h"
#include "../../math/Vector.h"
#include <iostream>

namespace Physics {
	// Constraint: The length must stay fixed, but rotation about the first object is allowed about a specified axis.
	class DistanceJoint : public JointConstraint {
	protected:
		float half_norm;

	public:
		DistanceJoint(Object* first, Object* second) {
			this->first = first;
			this->second = second;
			this->half_norm = PMath::norm(first->transform.position - second->transform.position) / 2.0f;
		}
		
		void ApplyConstraint(float delta) override {
			const PMath::Vector midpoint = PMath::midpoint(first->transform.position, second->transform.position);
			const PMath::Vector dir = PMath::normalize(first->transform.position - second->transform.position);

			if (first->GetType() != BodyType::STATIC && delta != 0) {
				first->old_transform.position = first->transform.position;
				first->transform.position = midpoint + dir * half_norm;
				first->old_transform.velocity = first->transform.velocity;
				first->transform.velocity += (first->transform.position - first->old_transform.position) / delta;
			}

			if (second->GetType() != BodyType::STATIC && delta != 0) {
				second->old_transform.position = second->transform.position;
				second->transform.position = midpoint - dir * half_norm;
				second->old_transform.velocity = second->transform.velocity;
				second->transform.velocity += (second->transform.position - second->old_transform.position) / delta;
			}
		}
	};
}


#endif