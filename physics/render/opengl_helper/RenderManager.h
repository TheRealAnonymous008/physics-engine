#ifndef RENDERMANAGER_H_INCLUDED
#define RENDERMANAGER_H_INCLUDED

#include <vector>
#include "../../core/geometry/Circle.h"
#include "../../core/geometry/Line.h"
#include "../../core/geometry/Quad.h"
#include "../../core/geometry/Triangle.h"
#include "../../core/geometry/Shape.h"
#include "../../core/links/RigidJoint.h"
#include "IndexBuffer.h"
#include "VertexManager.h"

#define CIRCLE_VERTICES 32

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

			Physics::Point* center = obj->GetCenter();
			float radius = obj->GetRadius();

			for (int i = 0; i < CIRCLE_VERTICES; ++i) {
				Physics::Point* pt = new Physics::Point();
				pt->SetId(-1);
				manager->AddVertex(pt);
				float angle = i * (2 * Physics::PI) / CIRCLE_VERTICES;
				pt->transform.position = center->transform.position + PMath::init(radius * cos(angle), radius * sin(angle));

				ind[i] = pt->GetId();
				obj->AddPrimitive(pt);
			}

			// Constrain each vertex
			auto prims = obj->GetPrimitives();
			for (int i = 0; i < CIRCLE_VERTICES; ++i) {
				obj->AddInternalConstraint(new Physics::RigidJoint(prims[i], center));
			}

			indices.push_back(ind);
			counts.push_back(CIRCLE_VERTICES);
			objects++;
		}

		void Render() {

			//for (int i = 0; i < objects; ++i) {
			//	int count = counts[i];
			//	unsigned int* ind = indices[i];
			//	for (int j = 0; j < count; ++j) {
			//		std::cout << ind[j] << " ";
			//	}
			//	std::cout << "\n";
			//}

			glMultiDrawElements(GL_LINE_LOOP, &counts[0], GL_UNSIGNED_INT, (const void**) &indices[0], objects);
		}
	};
}

#endif