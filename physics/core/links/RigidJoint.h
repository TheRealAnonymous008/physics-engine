#ifndef RIGIDJOINT_H_INCLUDED
#define RIGIDJOINT_H_INCLUDED

#include "JointConstraint.h"
#include "../../math/Vector.h"
#include <iostream>

namespace Physics {
	// Constraint: The length must stay fixed, but rotation about the first object is allowed about a specified axis.
	class RigidJoint : public JointConstraint {
	protected:
		PMath::Vector offset;

	public:
		RigidJoint(Object* first, Object* second) {
			this->first = first;
			this->second = second;
			this->offset = second->transform.position - first->transform.position;
		}

		void ApplyConstraint(float delta) override {
			PMath::Vector pos = first->transform.position;
			first->transform.position = second->transform.position - offset;
			first->old_transform.position = pos;

			pos = first->transform.velocity;
			first->transform.velocity += (first->transform.position - first->old_transform.position) / delta;
			first->old_transform.velocity = pos;
		}
	};
}


#endif