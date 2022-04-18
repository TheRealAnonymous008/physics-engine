#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "../points/Point.h"

namespace Physics {
	namespace Geometry {
		class Line {
		private:
			Point* p1;
			Point* p2;
		public:
			Line(Point* p1, Point* p2) {
				this->p1 = p1;
				this->p2 = p2;
			}

			Point** GetPoints() {
				Point* points[3] = { p1, p2};
				return points;
			}
		};
	}
}

#endif

