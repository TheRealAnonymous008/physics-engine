#ifndef POINTFACTORY_H_INCLUDED
#define POINTFACTORY_H_INCLUDED

#include "../points/Point.h"
#include "../../math/Vector.h"

namespace Physics {
	class PointFactory{
	private: 
		int id = 0;
		PointFactory() {
			
		}


	public:
		static PointFactory& GetInstance() {
			static PointFactory instance;

			return instance;
		}

		Point* MakePoint2D(float x, float y, BodyType type = BodyType::DYNAMIC) {
			Point* pt = new Point(type, id);
			pt->transform.position = PMath::init(x, y);
			id++;

			return pt;
		}

		PointFactory(const PointFactory& factory) = delete;
		void operator=(const PointFactory& factory) = delete;

	};
}

#endif