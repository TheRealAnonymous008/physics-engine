#ifndef GJK_H_INCLUDED
#define GJK_H_INCLUDED

#include "Collider.h"
#include "../../math/Vector.h"
#include "../../math/Utils.h"
#include <array>
#include <cmath>
#include <iostream>


#define MAX_GJK_ITER 16
// Implementation based on this video: https://www.youtube.com/watch?v=MDusDn8oTSE

namespace Physics {
	// Helper functions
	using namespace PMath;
	namespace Utils {
		inline Vector GetSupport(const Collider* c1, const Collider* c2, Vector dir) {
			return c1->FindFurthestPoint(dir) - c2->FindFurthestPoint(-dir);
		}

		struct Simplex {
		private:
			std::array<Vector, 4> points;
			unsigned int size;

		public:
			Simplex() {
				points = std::array<Vector, 4>();
				size = 0;
			}

			Simplex& operator=(std::initializer_list<Vector> list) {
				for (auto v = list.begin(); v != list.end(); ++v){
					points[std::distance(list.begin(), v)] = *v;
				}
				size = list.size();

				return *this;
			}

			void Push(Vector point) {
				points = { point, points[0], points[1], points[2] };
				size = std::min(size + 1, 4u);
			}

			Vector& operator[](int i) {
				return points[i];
			}

			unsigned Size() const {
				return size;
			}

			auto Begin() const {
				return points.begin();
			}

			auto End() const {
				return points.end() - (4 - size);
			}
		};


		// Helper functions for each case of the GJK algorithm
		bool GJKLine(Simplex& simplex, Vector& direction);
		bool GJKTriangle(Simplex& simplex, Vector& direction, int iters);

		bool GJKTetrahedron(Simplex& simplex, Vector& direction);
	
		bool GetNextSimplex(Simplex& simplex, Vector& direction);
		bool GJK(const Collider* A, const Collider* B);
	}
}

#endif