#include "Vector.h"

namespace PMath{
    const Vector init(float x, float y, float z, float w){
        return Vector{x, y, z, w};
    }

    const Vector operator -(const Vector& v){
        return Vector{-v.vec[0], -v.vec[1], -v.vec[2], -v.vec[3]};
    }

    const Vector operator +(const Vector& v1, const Vector& v2){
        Vector result;
        _mm_store_ps(result.vec, _mm_add_ps(v1.vec4, v2.vec4));
        return result;
    }

    const Vector operator -(const Vector& v1, const Vector& v2){
        Vector result;
        _mm_store_ps(result.vec, _mm_sub_ps(v1.vec4, v2.vec4));
        return result;
    }

    const Vector operator *(float c, const Vector& v){
        Vector result;
        Vector scalar = Vector{c, c, c, c};
        _mm_store_ps(result.vec, _mm_mul_ps(v.vec4, scalar.vec4));
        return result;
    }

    const Vector operator *(const Vector& v, float c){
        Vector result;
        Vector scalar = Vector{c, c, c, c};
        _mm_store_ps(result.vec, _mm_mul_ps(v.vec4, scalar.vec4));
        return result;
    }

	const Vector operator *(const Vector& v, const Vector& w) {
		Vector result;
		_mm_store_ps(result.vec, _mm_mul_ps(v.vec4, w.vec4));
		return result;
	}

    const Vector operator /(const Vector& v, float c){
		if (c == 0)
			return v;

        Vector result;
        Vector scalar = Vector{c, c, c, c};
        _mm_store_ps(result.vec, _mm_div_ps(v.vec4, scalar.vec4));
        return result;
    }

    void operator +=(Vector& v1, const Vector& v2){
        v1 = PMath::operator+(v1, v2);
    }

    void operator -=(Vector& v1, const Vector& v2){
        v1 = PMath::operator-(v1, v2);
    }

    void operator *=(Vector& v, float c){
        v = PMath::operator*(v, c);
    }

    void operator /=(Vector& v, float c){
        v = PMath::operator/(v, c);
    }

    const float hsum(const Vector& v) {
        // Horizontal sum based on https://stackoverflow.com/questions/6996764/fastest-way-to-do-horizontal-sse-vector-sum-or-other-reduction
        __m128 shuf = _mm_movehdup_ps(v.vec4);        // broadcast elements 3,1 to 2,0
        __m128 sums = _mm_add_ps(v.vec4, shuf);
        shuf        = _mm_movehl_ps(shuf, sums); // high half -> low half
        sums        = _mm_add_ss(sums, shuf);
        return        _mm_cvtss_f32(sums);
    }

    const float dot(const Vector& v1, const Vector& v2){
		Vector result;
		result.vec4= _mm_mul_ps(v1.vec4, v2.vec4);
        return PMath::hsum(result);
    }

    const float norm(const Vector& v){
        return sqrt(PMath::dot(v, v));
    }

    const Vector normalize(const Vector& v){
        float n = PMath::norm(v);
        return Vector{v.vec[0] / n, v.vec[1] / n, v.vec[2] / n, v.vec[3]/n};
    }

	const Vector cross(const Vector& v1, const Vector& v2) {
		float a1 = v1.vec[0];
		float a2 = v1.vec[1];
		float a3 = v1.vec[2];

		float b1 = v2.vec[0];
		float b2 = v2.vec[1];
		float b3 = v2.vec[2];

		float x = a2 * b3 - a3 * b2;
		float y = a3 * b1 - a1 * b3; 
		float z = a1 * b2 - a2 * b1;

		return PMath::init(x, y, z);
	}

	const Vector midpoint(const Vector& v1, const Vector& v2) {
		return (v1 + v2) / 2.0f;
	}

	bool is_same_dir(const Vector& v1, const Vector& v2) {
		return dot(v1, v2) > 0;
	}

    const bool operator ==(const Vector& v1, const Vector& v2){
        return PMath::norm(PMath::operator-(v1, v2)) <= EQUALITY_THRESHOLD;
    }

    std::ostream& operator <<(std::ostream& os, const Vector& v){
        return os << "["<<v.vec[0]<<",\t"<<v.vec[1]<<",\t"<<v.vec[2]<<",\t"<<v.vec[3]<<"]";
    }
}
