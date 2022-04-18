#ifndef QUAD_H_INCLUDED
#define QUAD_H_INCLUDED

#include "../points/Point.h"

namespace Physics {
	namespace Geometry {
		class Quad {
		private:
			Point* p1;
			Point* p2;
			Point* p3;
			Point* p4;
		public:
			Quad(Point* p1, Point* p2, Point* p3, Point* p4) {
				this->p1 = p1;
				this->p2 = p2;
				this->p3 = p3;
				this->p4 = p4;
			}

			Point** GetPoints() {
				Point* points[4] = { p1, p2, p3, p4 };
				return points;
			}
		};
	}
}

#endif

