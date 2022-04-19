#ifndef SCALER_H_INCLUDED
#define SCALER_H_INCLUDED

#include "../../math/Vector.h"

namespace GLPhysX {
	inline PMath::Vector  Scale(PMath::Vector x, int width, int height) {
		return PMath::init(x.vec[0] / width, x.vec[1] / height, x.vec[2], x.vec[3]);
	}
}

#endif