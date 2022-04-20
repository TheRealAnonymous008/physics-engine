#ifndef VERTEXMANAGER_H_INCLUDED
#define VERTEXMANAGER_H_INCLUDED

#include "../../core/points/Point.h"
#include "VertexArrayObject.h"
#include <vector>

namespace GLPhysX {
	class VertexManager{
	private:
		std::vector<Physics::Point*> vertices;
		GL::VertexArrayObject* VAO;
		int width;
		int height;


	public:
		VertexManager(int width, int height) {
			vertices = std::vector<Physics::Point*>();
			this->VAO = new GL::VertexArrayObject();
			this->height = height;
			this->width = width;
		}

		void AddVertex(Physics::Point* pt) {
			this->vertices.push_back(pt);
			VAO->AddVertex3D(GLPhysX::Scale(pt->transform.position, width, height).vec);
		}

		void UpdateVertices() {
			VAO->Clear();
			for (Physics::Point* pt : vertices) {
				VAO->AddVertex3D(GLPhysX::Scale(pt->transform.position, width, height).vec);
			}
			VAO->Bind();
		}

		void Bind(){
			VAO->Bind();
		}

		void UnBind() {
			VAO->UnBind();
		}

		void GenerateArrays() {
			VAO->GenerateArrays();
		}
		
		void SpecifyLayout() {
			VAO->SpecifyLayout();
		}

		float* GetVertices() const{
			return VAO->GetVertices();
		}

		unsigned int GetLength() const {
			return VAO->GetLength();
		}

		
	};
}

#endif