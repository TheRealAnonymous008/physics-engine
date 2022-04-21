#ifndef POINTFACTORY_H_INCLUDED
#define POINTFACTORY_H_INCLUDED

#include "../points/Point.h"
#include "../points/Emitter.h"
#include "../points/RadialEmitter.h"
#include "../../math/Vector.h"

namespace Physics {
	class PointFactory{
	private: 
		unsigned long long int id = 0;
		PointFactory() {
			
		}


	public:
		static PointFactory& GetInstance() {
			static PointFactory instance;

			return instance;
		}

		Point* Make(Point* point) {
			point->SetId(id);
			id++;
			return point;
		}

		Point* MakePoint2D(const PMath::Vector& pos, const BodyType& type = BodyType::DYNAMIC) {
			Point* pt = new Point(type, id);
			pt->transform.position = pos;
			id++;

			return pt;
		}

		Emitter* MakeEmitter2D(const PMath::Vector& force, const PMath::Vector& pos, const BodyType& type = BodyType::STATIC) {
			Emitter* em = new Emitter(force, type, id);
			em->transform.position = pos;
			id++;

			return em;
		}

		RadialEmitter* MakeRadialEmitter2D(const float force, const PMath::Vector& pos, const BodyType& type = BodyType::STATIC) {
			RadialEmitter* rem = new RadialEmitter(force, 1.0f, 2.0f, type, id);
			rem->transform.position = pos;
			id++;
			
			return rem;
		}

		PointFactory(const PointFactory& factory) = delete;
		void operator=(const PointFactory& factory) = delete;

	};
}

#endif