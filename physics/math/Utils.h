#ifndef MATHUTILS_H_INCLUDED
#define MATHUTILS_H_INCLUDED

#ifndef EQUALITY_THRESHOLD
#define EQUALITY_THRESHOLD 1e-10
#endif

#include <cmath>
 namespace PMath {
	inline bool close_equal(float a, float b) {
		return std::fabs(a - b) < EQUALITY_THRESHOLD;
	}
}

#endif