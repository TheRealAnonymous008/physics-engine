#ifndef QUAD_H_INCLUDED
#define QUAD_H_INCLUDED

#include "Shape.h"
#include "../points/Point.h"
#include "../links/DistanceJoint.h"

namespace Physics {
	namespace Geometry {
		// A shape with 4 vertices
		class Quad : public Shape{
		public:
			Quad(Point* p1, Point* p2, Point* p3, Point* p4) {
				this->points.push_back(p1);
				this->points.push_back(p2);
				this->points.push_back(p3);
				this->points.push_back(p4);
			}
		};

		// A quad with fixed side lengths
		class RigidQuad : public Quad {
		public:
			RigidQuad(Point* p1, Point* p2, Point* p3, Point* p4) : Quad(p1, p2, p3, p4){
				this->constraints.push_back(new DistanceJoint(p1, p2));
				this->constraints.push_back(new DistanceJoint(p2, p3));
				this->constraints.push_back(new DistanceJoint(p3, p4));
				this->constraints.push_back(new DistanceJoint(p4, p1));
			}
		};
	}
}

#endif

