#ifndef QUAD_H_INCLUDED
#define QUAD_H_INCLUDED

#include "Shape.h"
#include "../points/Point.h"

namespace Physics {
	namespace Geometry {
		class Quad : public Shape{
		public:
			Quad(Point* p1, Point* p2, Point* p3, Point* p4) {
				this->points.push_back(p1);
				this->points.push_back(p2);
				this->points.push_back(p3);
				this->points.push_back(p4);
			}
		};
	}
}

#endif

