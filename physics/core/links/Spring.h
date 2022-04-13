#ifndef SPRING_H_INCLUDED
#define SPRING_H_INCLUDED

#include "../Object.h"
#include "JointConstraint.h"
#include "../../math/Vector.h"
#include <iostream>
namespace Physics {
	class Spring : public JointConstraint{
	protected:
		float k;
		float rest_length;

	public:
		// k is the spring constant.
		// l0 is the resting length
		Spring(Object* first, Object* second, float k = 1.0f, float rest_length = 1.0f) {
			this->first = first;
			this->second = second;
			this->k =k * NEWTON / M;
			this->rest_length = rest_length * M;
		}

		// Apply the constraint based on Hooke's Law
		// Measure displacement from the middle of the endpoints in case they are DYNAMIC Objects.
		void ApplyConstraint(float delta) override {
			const PMath::Vector direction = PMath::normalize(second->transform.position - first->transform.position);
			const float displacement = PMath::norm(second->transform.position - first->transform.position) - rest_length;

			second->ApplyForce(-k * displacement * direction);
			first->ApplyForce(k * displacement * direction);
		}

		void SetSpringConstant(float k) {
			this->k = k * NEWTON / M;
		}

		float GetScaledSpringConstant() {
			return this->k;
		}

		float GetSpringConstant() {
			return this->k / (NEWTON / M);
		}

		float GetLength() {
			return rest_length;
		}

		void SetLength(float length) {
			this->rest_length = length;
		}
		
	};
}


#endif