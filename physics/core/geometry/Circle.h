#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "../points/Point.h"

namespace Physics {
	namespace Geometry {
		class Circle {
		private:
			Point* center;
			float x_radius;
			float y_radius;

		public:
			Circle(Point* center, float radius) {
				this->center = center;
				x_radius = radius;
				y_radius = radius;
			}

			Circle(Point* center, float x_radius, float y_radius) {
				this->center = center;
				this->x_radius = x_radius;
				this->y_radius = y_radius;
			}

			Point* GetCenter() {
				return center;
			}

			float GetXRadius() {
				return x_radius;
			}

			float GetYRadius() {
				return y_radius;
			}
		};
	}
}

#endif

