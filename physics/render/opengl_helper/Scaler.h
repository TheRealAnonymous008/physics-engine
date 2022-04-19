#ifndef SCALER_H_INCLUDED
#define SCALER_H_INCLUDED

#include "../../math/Vector.h"
#include <iostream>

#define BIG_NUMBER 1e12
namespace GLPhysX {

	inline int Discretize(float x) {
		return (x * BIG_NUMBER) / BIG_NUMBER;
	}

	inline PMath::Vector  Scale(PMath::Vector v, int width, int height) {
		width /= 2;
		height /= 2;

		// Discretize a bit so smaller perturbations are unlikely 
		float x = 1.0 * Discretize(v.vec[0]) / width;
		float y = -1.0 * Discretize(v.vec[1]) / height;
		float z = 1.0 * Discretize(v.vec[2]);
		float w = 1.0 * Discretize(v.vec[3]);

		// Need the - on the y coordinate so down points down.
		return PMath::init(x, y, z, w);
	}
}

#endif