#ifndef RENDERMANAGER_H_INCLUDED
#define RENDERMANAGER_H_INCLUDED

#include <vector>
#include "../../core/geometry/Circle.h"
#include "../../core/geometry/Line.h"
#include "../../core/geometry/Quad.h"
#include "../../core/geometry/Triangle.h"
#include "../../core/geometry/Shape.h"
#include "IndexBuffer.h"
#include "VertexManager.h"

#define CIRCLE_VERTICES 100

namespace GLPhysX {
	class RenderManager{
	private:
		std::vector<unsigned int*> indices = std::vector<unsigned int*>();
		std::vector<GLsizei> counts = std::vector<GLsizei>();
		int objects = 0;
		VertexManager* manager;


	public:
		RenderManager(VertexManager* manager) {
			this->manager = manager;
		}

		void AddPoint(Physics::Point* obj) {
			manager->AddVertex(obj);
			unsigned int* ind = (unsigned int*) malloc(sizeof(unsigned int));
			ind[0] = obj->GetId();

			indices.push_back(ind);
			counts.push_back(1);

			objects++;
		}

		void AddLine(Physics::Geometry::Line* obj) {
			
			unsigned int* ind = (unsigned int*)malloc(2 * sizeof(unsigned int));
			for (int i = 0; i < 2; ++i) {
				manager->AddVertex(obj->GetPrimitives()[i]);
				ind[i] = obj->GetPrimitives()[i]->GetId();
			}

			indices.push_back(ind);
			counts.push_back(2);
			objects++;
		}

		void AddTriangle(Physics::Geometry::Triangle* obj) {

			unsigned int* ind = (unsigned int*)malloc(3 * sizeof(unsigned int));

			for (int i = 0; i < 3; ++i) {
				manager->AddVertex(obj->GetPrimitives()[i]);
				ind[i] = obj->GetPrimitives()[i]->GetId();
			}

			indices.push_back(ind);
			counts.push_back(3);
			objects++;
		}

		void AddQuad(Physics::Geometry::Quad* obj) {

			unsigned int* ind = (unsigned int*)malloc(4 * sizeof(unsigned int));

			for (int i = 0; i < 4; ++i) {
				manager->AddVertex(obj->GetPrimitives()[i]);
				ind[i] = obj->GetPrimitives()[i]->GetId();
			}

			indices.push_back(ind);
			counts.push_back(4);
			objects++;
		}

		void AddCircle(Physics::Geometry::Circle* obj) {
			unsigned int* ind = (unsigned int*)malloc(CIRCLE_VERTICES * sizeof(unsigned int));

			for (int i = 0; i < CIRCLE_VERTICES; ++i) {
				manager->AddVertex(obj->GetPrimitives()[i]);
				ind[i] = obj->GetPrimitives()[i]->GetId();
			}

			indices.push_back(ind);
			counts.push_back(4);
			objects++;
		}

		void Render() {
			glMultiDrawElements(GL_LINE_LOOP, &counts[0], GL_UNSIGNED_INT, (const void**) &indices[0], objects);
		}
	};
}

#endif