#ifndef HINGEJOINT_H_INCLUDED
#define HINGEJOINT_H_INCLUDED

#include "JointConstraint.h"
#include "../../math/Vector.h"
#include <iostream>

namespace Physics {
	class HingeJoint : public JointConstraint {
	protected:

	public:
		HingeJoint(Object* first, Object* second) {
			this->first = first;
			this->second = second;
		}
		
		// Constraint: The length must stay fixed, but rotation about the first object is allowed about a specified axis.
		void ApplyConstraint(float delta) override {
			const float norm = PMath::norm(first->transform.position - second->transform.position);
		}
	};
}


#endif