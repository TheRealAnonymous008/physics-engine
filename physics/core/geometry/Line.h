#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "Shape.h"
#include "../points/Point.h"

namespace Physics {
	namespace Geometry {
		class Line : public Shape{
		public:
			Line(Point* p1, Point* p2) {
				this->points.push_back(p1);
				this->points.push_back(p2);
			}
		};
	}
}

#endif

