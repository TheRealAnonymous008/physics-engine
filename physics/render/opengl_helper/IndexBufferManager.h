#ifndef INDEXBUFFERMANAGER_H_INCLUDED
#define INDEXBUFFERMANAGER_H_INCLUDED

#include "../../core/points/Point.h"
#include "IndexBuffer.h"
#include <vector>

namespace GLPhysX {
	class IndexBufferManager {
	private:
		std::vector<unsigned int> indices;

	public:
		IndexBufferManager() {
			indices = std::vector<unsigned int>();
		}

		GL::IndexBufferObject* GenerateIB() {
			return new GL::IndexBufferObject(&indices[0], indices.size());
		}

		void AddIndex1D(int a) {
			indices.push_back(a);
		}

		void AddIndex2D(int a, int b) {
			indices.push_back(a);
			indices.push_back(b);
		}

		void AddIndex3D(int a, int b, int c) {
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
		}

		unsigned int* GetIndex(int start = 0) {
			return &indices[0] + start;
		}
	};
}

#endif