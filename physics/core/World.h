#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include "Object.h"

namespace Physics {
	class World {
	private:
		std::vector<Object*> entities;

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

	};
}

#endif
