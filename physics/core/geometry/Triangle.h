#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "../points/Point.h"

namespace Physics {
	namespace Geometry {
		class Triangle {
		private:
			Point* p1; 
			Point* p2;
			Point* p3;
		public:
			Triangle(Point* p1, Point* p2, Point* p3) {
				this->p1 = p1;
				this->p2 = p2;
				this->p3 = p3;
			}

			Point** GetPoints() {
				Point* points[3] = { p1, p2, p3 };
				return points;
			}
		};
	}
}

#endif

