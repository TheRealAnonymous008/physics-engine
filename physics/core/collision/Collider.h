#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include "../../math/Vector.h"

namespace Physics {
	class Collider {
	public:
		Collider() {

		}

		virtual PMath::Vector FindFurthestPoint(PMath::Vector dir) const = 0;

	};
}


#endif