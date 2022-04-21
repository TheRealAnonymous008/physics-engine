#ifndef RENDERMANAGER_H_INCLUDED
#define RENDERMANAGER_H_INCLUDED

#include <vector>
#include "GLWrappers.h"

namespace GLPhysX {
	class RenderManager{
	private:
		std::vector<GLPhysX::Object*> objects;

	public:
		RenderManager() {
			objects = std::vector<GLPhysX::Object*>();
		}

		void Add(GLPhysX::Object* obj) {
			objects.push_back(obj);
		}

		void Render() {
			unsigned long long int index = 0;
			for (GLPhysX::Object* obj : objects) {
				obj->Render(&index);
			}
		}

		
	};
}

#endif