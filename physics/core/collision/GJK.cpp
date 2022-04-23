#include "GJK.h"
#include <iostream>

using namespace Physics::Utils;
using namespace PMath;

bool Physics::Utils::GJKLine(Simplex& simplex, Vector& direction) {
	Vector a = simplex[0];
	Vector b = simplex[1];

	Vector ab = b - a;
	Vector a0 = -a;

	if (is_same_dir(ab, a0)) {
		direction = cross(cross(ab, a0), ab);
	}

	else {
		simplex = { a };
		direction = a0;
	}

	return false;
}

bool Physics::Utils::GJKTriangle(Simplex& simplex, Vector& direction, int iters = 0) {
	if (iters > MAX_GJK_ITER) {
		return false;
	}

	Vector a = simplex[0];
	Vector b = simplex[1];
	Vector c = simplex[2];

	Vector ab = b - a;
	Vector ac = c - a;
	Vector ao = -a;

	Vector abc = cross(ab, ac);

	if (is_same_dir(cross(ab, abc), ao)) {
		direction = cross(cross(ab, ao), ao);
		return GJKLine(simplex = { b, a }, direction);
	}
	else if (is_same_dir(cross(abc, ac), ao)) {
		direction = cross(cross(ac, ao), ac);
		return GJKLine(simplex = { c, a }, direction);
	}
	else {
		float v = dot(abc, ao);
		if (close_equal(v, 0))
			return true;
		else if (v > 0) {
			return Physics::Utils::GJKTriangle(simplex = { a, b, c }, direction = abc, iters + 1);
		}
		else {
			return Physics::Utils::GJKTriangle(simplex = { c, a, b }, direction = -abc, iters + 1);
		}
	}
}


bool Physics::Utils::GJKTetrahedron(Simplex& simplex, Vector& direction) {
	Vector a = simplex[0];
	Vector b = simplex[1];
	Vector c = simplex[2];
	Vector d = simplex[3];

	Vector ab = b - a;
	Vector ac = c - a;
	Vector ad = d - a;
	Vector a0 = -a;

	Vector abc = cross(ab, ac);
	Vector acd = cross(ac, ad);
	Vector adb = cross(ad, ab);


	if (is_same_dir(abc, a0)) {
		return GJKTriangle(simplex = { a, b, c }, direction);
	}

	if (is_same_dir(acd, a0)) {
		return GJKTriangle(simplex = { a, c, d }, direction);
	}

	if (is_same_dir(adb, a0)) {
		return GJKTriangle(simplex = { a, d, b }, direction);
	}

	return true;
}

bool Physics::Utils::GetNextSimplex(Simplex& simplex, Vector& direction) {
	switch (simplex.Size()) {
	case 1: return direction == PMath::init();
	case 2: return GJKLine(simplex, direction);
	case 3: return GJKTriangle(simplex, direction);
	case 4: return GJKTetrahedron(simplex, direction);
	}
	return false;
}


bool Physics::Utils::GJK(const Collider* A, const Collider* B) {
	Vector support = GetSupport(A, B, PMath::init(1));

	Simplex simplex;
	simplex.Push(support);

	Vector direction = -support;
	int iters = 0;

	while (true && iters < MAX_GJK_ITER) {
		// Degenerate case of 0-simplex and 1-simplex
		if (direction == PMath::init())
			return true;

		support = GetSupport(A, B, direction);
		if (dot(support, direction) <= 0)
			return false;

		simplex.Push(support);
		if (GetNextSimplex(simplex, direction)) {
			return true;
		}

		++iters;
	}

	return false;
}