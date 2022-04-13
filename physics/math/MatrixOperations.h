#ifndef MATRIXOPERATIONS_H_INCLUDED
#define MATRIXOPERATIONS_H_INCLUDED

#include "Matrix.h"

// Specialized Matrix Operations for efficiency

using namespace PMath;
float determinant_2x2(const PhysicsMatrix& M) {
	float m11 = M.rows[0].vec[0];
	float m12 = M.rows[0].vec[1];
	float m21 = M.rows[1].vec[0];
	float m22 = M.rows[1].vec[1];

	return m11 * m22 - m12 * m21;
}

float determinant_3x3(const PhysicsMatrix& M) {
	float a1 = M.rows[0].vec[0];
	float b1 = M.rows[0].vec[1];
	float c1 = M.rows[0].vec[2];

	float a2 = M.rows[1].vec[0];
	float b2 = M.rows[1].vec[1];
	float c2 = M.rows[1].vec[2];

	float a3 = M.rows[2].vec[0];
	float b3 = M.rows[2].vec[1];
	float c3 = M.rows[2].vec[2];

	return (a1 * b2 * c3 + b1 * c2 * a3 + c1 * a2 * b3) - (a3 * b2 * c1 + b3 * c2 * a1 + c3 * a2 * b1);
}

#endif