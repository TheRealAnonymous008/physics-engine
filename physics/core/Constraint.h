#ifndef CONSTRAINT_H_INCLUDED
#define CONSTRAINT_H_INCLUDED

#include "Object.h"

namespace Physics {
	// An interaction between two Objects that limits the dynamics of these objects
	class Constraint  {
	public:
		Constraint() {

		}

		virtual void ApplyConstraint(float delta) {
			// Apply a constraint to the objects stored.
		}
	};
}

#endif