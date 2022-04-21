#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "Shape.h"
#include "../points/Point.h"
#include "../links/DistanceJoint.h"

namespace Physics {
	namespace Geometry {
		// A shape with 3 points as vertices
		class Triangle : public Shape{
		protected: 
			Point* center = nullptr;

		public:
			Triangle(Point* p1, Point* p2, Point* p3) {
				this->points.push_back(p1);
				this->points.push_back(p2);
				this->points.push_back(p3);
			}

			Point* GetCenter() {
				if (center == nullptr) {
					center = new Point();
					center->transform.position = (points[0]->transform.position + points[1]->transform.position + points[2]->transform.position) / 3.0f;

					this->constraints.push_back(new DistanceJoint(points[0], center));
					this->constraints.push_back(new DistanceJoint(points[1], center));
					this->constraints.push_back(new DistanceJoint(points[2], center));
				}
				return center;
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

