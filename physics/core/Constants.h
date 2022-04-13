#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include "../math/Vector.h"

namespace Physics{
	// Damping coefficient to compensate for numerical errors in evaluating velocity
	constexpr auto DEFAULT_DAMPING_COEFFICIENT = 0.9995f;
	// Smoothing coefficient to prevent particles from flying too fast when they get too close to an emitter.
	constexpr auto DEFAULT_SMOOTHING_COEFFICIENT = 1.0f / 32.0f;



	constexpr auto GRAVITATIONAL_CONSTANT = 6.674098e-10f;

	// Scale factors based on the SI units
    namespace Units{
        static float M = 1;
        static float KG = 1;
        static float S = 1;
//        static float MOL = 1;
//        static float AMP = 1;
//        static float K = 1;
//        static float CD = 1;

        static PMath::Vector UP = PMath::init(0, -1, 0);
        static PMath::Vector DOWN = PMath::init(0, 1, 0);
        static PMath::Vector RIGHT = PMath::init(1, 0, 0);
        static PMath::Vector LEFT = PMath::init(-1, 0, 0);
        static PMath::Vector FRONT = PMath::init(0, 0, 1);
        static PMath::Vector BACK = PMath::init(0, 0, -1);

		// Derived units
		static float NEWTON = KG * M / (S * S);
    }
}
#endif // CONSTANTS_H_INCLUDED
