#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <iostream>
#include "Object.h"
#include "../math/Vector.h"

// TODO: Emitter type objects should be connected to the objects they can handle by way of a bipartite graph for efficiency.


namespace Physics {
	using namespace Units;
	class World {
	private:
		std::vector<Object*> entities;
		PMath::Vector force;
		bool has_gravity = false;

	public:
		World() {
			entities = std::vector<Object*>();
		}

		void AddEntity(Object* p) {
			this->entities.push_back(p);
		}

		const std::vector<Object*> GetEntitites() const {
			return this->entities;
		}

		const void ApplyForce() {
			for (Object* obj : entities) {
				obj->ApplyForce(force);
			}
		}

		const PMath::Vector GetForce() const{
			return force;
		}

		void AddForce(const PMath::Vector& force) {
			this->force += force;
		}

		void ApplyGravity() {
			this->force += 9.82f * M / (S * S) * KG * DOWN;
			has_gravity = true;
		}

		void RemoveGraivty() {
			if (has_gravity){
				this->force -= 9.82f * M / (S * S) * KG * DOWN;
				has_gravity = false;
			}
		}
	};
}

#endif
