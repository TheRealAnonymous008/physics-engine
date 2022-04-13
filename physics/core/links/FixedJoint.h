#ifndef FIXEDJOINT_H_INCLUDED
#define FIXEDJOINT_H_INCLUDED

#include "../Object.h"
#include "../../math/Vector.h"
#include <iostream>

namespace Physics {
	class FixedJoint : public Object {
	protected:
		Object* first;
		Object* second;
		float length;

	public:
		// k is the spring constant.
		// l0 is the resting length
		FixedJoint(Object* first, Object* second, float length = 1.0f) {
			this->first = first;
			this->second = second;
			this->length = M * length;
		}

		// Apply the constraint based on Hooke's Law
		// Measure displacement from the middle of the endpoints in case they are DYNAMIC Objects.
		void Update(float delta) override {
			
		}

		float GetLength() {
			return length;
		}

		void SetLength(float length) {
			this->length = length;
		}

	};
}


#endif