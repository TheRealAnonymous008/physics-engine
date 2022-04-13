#ifndef CONSTRAINT_H_INCLUDED
#define CONSTRAINT_H_INCLUDED

#include "Object.h"

namespace Physics {
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