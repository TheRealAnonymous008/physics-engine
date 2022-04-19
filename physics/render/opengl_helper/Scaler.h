#ifndef SCALER_H_INCLUDED
#define SCALER_H_INCLUDED

#include "../../math/Vector.h"

namespace GLPhysX {
	inline PMath::Vector  Scale(PMath::Vector x, int width, int height) {
		width /= 2;
		height /= 2;

		// Need the - on the y coordinate so down points down.
		return PMath::init(x.vec[0] / width, -x.vec[1] / height, x.vec[2], x.vec[3]);
	}
}

#endif