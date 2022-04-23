#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <vector>
#include "../math/Vector.h"
#include "Constants.h"
#include "Constraint.h"
#include "collision/Collider.h"

namespace Physics {
	struct Transform {
		PMath::Vector position = PMath::init(0, 0, 0, 0);
		PMath::Vector velocity = PMath::init(0, 0, 0, 0);
		PMath::Vector acceleration = PMath::init(0, 0, 0, 0);

		float mass = Units::KG;
	};

	enum BodyType {
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

	using namespace Units;
	// Generic Physics Object that populate the Physics World and is simulated by the Engine.
	class Object{ 
	protected:
		BodyType type;
		std::vector<Constraint*> constraints;
		Collider* collider = nullptr;

	public: 
		Transform transform;
		Transform old_transform;

		Object() {
			// Default constructor
		}

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

		virtual std::vector<Object*> GetPrimitives() {
			return std::vector<Object*>({ this });
		}

		virtual unsigned long long int GetId() {
			return 0;
		}

		virtual void SetId(unsigned long long int id) {
			
		}

		void UpdateInternalConstraints(float delta) {
			for (int i = 0; i < CONSTRAINT_SOLVER_RUNS; i++) {
				for (Constraint* c : constraints) {
					c->ApplyConstraint(delta);
				}
			}
		}

		void AddInternalConstraint(Constraint* constraint) {
			this->constraints.push_back(constraint);
		}

		virtual void AddPrimitive(Object* p) {
			
		}

		virtual void ApplyForce(PMath::Vector force) {
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

		virtual void Cleanup() {
			transform.acceleration = { 0, 0, 0, 0 };
		}

		virtual void SetType(BodyType type) {
			this->type = type;
		}

		virtual void AttachCollider(Collider* col) {
			this->collider = col;
		}

		Collider* GetCollider() {
			return collider;
		}

		BodyType GetType() {
			return this->type;
		}
	};
}

#endif 