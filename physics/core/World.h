#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <iostream>
#include "Object.h"
#include "Constraint.h"
#include "../math/Vector.h"

// TODO: Emitter type objects should be connected to the objects they can handle by way of a bipartite graph for efficiency.


namespace Physics {
	using namespace Units;
	class World {
	private:
		std::vector<Object*> entities;
		std::vector<Constraint*> constraints;
		PMath::Vector force;
		bool has_gravity = false;

	public:
		World() {
			entities = std::vector<Object*>();
			constraints = std::vector<Constraint*>();
		}

		void ApplyConstraintRandomization() {
			std::random_shuffle(constraints.begin(), constraints.end());
		}

		void ApplyEntityRandomization() {
			std::random_shuffle(entities.begin(), entities.end());
		}

		void AddEntity(Object* p) {
			this->entities.emplace_back(p);
		}

		const std::vector<Object*> GetEntitites() const {
			return this->entities;
		}

		void AddConstraint(Constraint* c) {
			this->constraints.push_back(c);
		}

		const std::vector<Constraint*> GetConstraints() const {
			return this->constraints;
		}

		const void ApplyForce() {
			for (Object* obj : entities) {
				obj->ApplyForce(force * obj->transform.mass);
			}
		}

		const void ApplyConstraints(float delta) {
			for (int i = 0; i < CONSTRAINT_SOLVER_RUNS; i++) {
				for (Constraint* c : constraints) {
					c->ApplyConstraint(delta);
				}
			}
		}

		const PMath::Vector GetForce() const{
			return force;
		}

		void AddForce(const PMath::Vector& force) {
			this->force += force;
		}
		
		void RemoveForce(const PMath::Vector& force) {
			this->force -= force;
		}

		void ApplyGravity() {
			this->force += 9.82f * NEWTON * DOWN;
			has_gravity = true;
		}

		void RemoveGraivty() {
			if (has_gravity){
				this->force -= 9.82f * NEWTON * DOWN;
				has_gravity = false;
			}
		}
		
	};
}

#endif
