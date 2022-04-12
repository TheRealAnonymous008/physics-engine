#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "../math/Vector.h"
#include "Constants.h"

namespace Physics {
	struct Transform {
		PMath::Vector position;
		PMath::Vector velocity;
		PMath::Vector acceleration;

		float mass = Units::KG;
	};


	using namespace Units;
	class Object{ 
	public: 
		Transform transform;

		virtual void Update(float delta) {
			// Called per update 
		}

		virtual void OnFrameStart(float delta) {
			// Called at the start of a Physics frame.
		}

		virtual void OnFrameEnd(float delta){
			// Called at the end of a Physics frame.
		}

		virtual void OnUpdate(float delta) {
			// Called after an update
		}

		void ApplyForce(PMath::Vector force) {
			// Apply a force to the object
			transform.acceleration += force / transform.mass;
		}

		void SetMass(float mass) {
			if (mass != 0)
				transform.mass = mass * KG;
		}

		void SetInverseMass(float mass) {
			if (mass == 0)
				transform.mass = INT_MAX * 1.0f;
			else
				transform.mass = (1.0f / mass) * KG;
		}

		void Cleanup() {
			transform.acceleration = { 0, 0, 0, 0 };
		}

	};
}

#endif 