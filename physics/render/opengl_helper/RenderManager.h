#ifndef RENDERMANAGER_H_INCLUDED
#define RENDERMANAGER_H_INCLUDED

#include <vector>
#include "GLWrappers.h"
#include "IndexBuffer.h"
#include "VertexManager.h"

namespace GLPhysX {
	class RenderManager{
	private:
		std::vector<GLPhysX::Point*> points = std::vector<GLPhysX::Point*>();
		std::vector<GLPhysX::RigidTriangle*> triangles = std::vector<GLPhysX::RigidTriangle*>();
		std::vector<GLPhysX::Line*> lines = std::vector<GLPhysX::Line*>();

		unsigned int line_i[2] = { 0, 1 };
		GL::IndexBufferObject* line_indices = new GL::IndexBufferObject(line_i, 2);

		unsigned int tri_i[3] = { 0, 1, 2 };
		GL::IndexBufferObject* triangle_indices = new GL::IndexBufferObject(tri_i, 3);

		VertexManager* manager;


	public:
		RenderManager(VertexManager* manager) {
			this->manager = manager;
		}

		void AddPoint(Physics::Point* obj) {
			points.push_back(new GLPhysX::Point(obj));
			manager->AddVertex(obj);
		}

		void AddTriangle(Physics::Geometry::RigidTriangle* obj) {
			triangles.push_back(new GLPhysX::RigidTriangle(obj));
			manager->AddVertex(obj->GetPrimitives()[0]);
			manager->AddVertex(obj->GetPrimitives()[1]);
			manager->AddVertex(obj->GetPrimitives()[2]);
		}

		void AddLine(Physics::Geometry::Line* obj) {
			lines.push_back(new GLPhysX::Line(obj));
			manager->AddVertex(obj->GetPrimitives()[0]);
			manager->AddVertex(obj->GetPrimitives()[1]);
		}

		void Render() {
			unsigned long long int index = 0;
			for (GLPhysX::Point* obj : points) {
				obj->Render(&index);
			}			
			
			triangle_indices->Bind();

			for (GLPhysX::RigidTriangle* obj : triangles) {
				obj->Render(&index);
			}

			triangle_indices->UnBind();

			line_indices->Bind();

			for (GLPhysX::Line* obj : lines) {
				obj->Render(&index);
			}

			line_indices->UnBind();

		}
	};
}

#endif