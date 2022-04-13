#ifndef JOINTCONSTRAINT_H_INCLUDED
#define JOINTCONSTRAINT_H_INCLUDED

#include "../Object.h"
#include "../Constraint.h"

namespace Physics {
	class JointConstraint : public Constraint{
	protected:
		Object* first;
		Object* second;

	public:
		JointConstraint() {

		}

		JointConstraint(Object* first, Object* second) {
			this->first = first;
			this->second = second;
		}
	};
}

#endif