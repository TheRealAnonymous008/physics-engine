#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "Shape.h"
#include "../points/Point.h"
#include "../links/DistanceJoint.h"

namespace Physics {
	namespace Geometry {
		// A shape with 3 points as vertices
		class Triangle : public Shape{
		public:
			Triangle(Point* p1, Point* p2, Point* p3) {
				this->points.push_back(p1);
				this->points.push_back(p2);
				this->points.push_back(p3);
			}
		};
		
		// A triangle with fixed side lengths
		class RigidTriangle : public Triangle {
		public:
			RigidTriangle(Point* p1, Point* p2, Point* p3) : Triangle(p1, p2, p3){
				this->constraints.push_back(new DistanceJoint(p1, p2));
				this->constraints.push_back(new DistanceJoint(p2, p3));
				this->constraints.push_back(new DistanceJoint(p1, p3));
			}
		};
	}
}

#endif

