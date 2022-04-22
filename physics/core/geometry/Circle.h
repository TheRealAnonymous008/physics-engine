#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "Shape.h"
#include "../points/Point.h"

namespace Physics {
	namespace Geometry {
		class Circle : public Geometry::Shape{
		private:
			Point* center;
			float radius;

		public:
			Circle(Point* center, float radius) {
				this->center = center;
				this->radius = radius;
			}

			Point* GetCenter() {
				return center;
			}
			
			float GetRadius() {
				return radius;
			}
		};
	}
}

#endif

