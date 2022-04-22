#ifndef VERTEXMANAGER_H_INCLUDED
#define VERTEXMANAGER_H_INCLUDED

#include "../../core/Object.h"
#include "VertexArrayObject.h"
#include <vector>
#include <set>

namespace GLPhysX {
	class VertexManager{
	private:
		std::vector<Physics::Object*> vertices;
		std::set<unsigned long long int> ids;
		GL::VertexArrayObject* VAO;
		int width;
		int height;

		unsigned long long int ctr = 0;


	public:
		VertexManager(int width, int height) {
			vertices = std::vector<Physics::Object*>();
			ids = std::set<unsigned long long int>();
			this->VAO = new GL::VertexArrayObject();
			this->height = height;
			this->width = width;
		}

		void AddVertex(Physics::Object* pt) {
			if (ids.count(pt->GetId()))
				return;

			this->vertices.push_back(pt);
			VAO->AddVertex3D(GLPhysX::Scale(pt->transform.position, width, height).vec);
			pt->SetId(ctr);
			ids.emplace(pt->GetId());
			ctr++;
		}

		void UpdateVertices() {
			VAO->Clear();
			for (Physics::Object* pt : vertices) {
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