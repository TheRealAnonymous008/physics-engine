#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "nmmintrin.h"
#include <ostream>

#define EQUALITY_THRESHOLD 1e-10


namespace PMath{
    typedef union {__m128 vec4; float vec[4];} Vector;

    const Vector init(float w = 0, float x = 0, float y = 0, float z = 0);
    const Vector operator -(const Vector& v);

    const Vector operator +(const Vector& v1, const Vector& v2);
    const Vector operator -(const Vector& v1, const Vector& v2);
    const Vector operator *(const Vector& v, float c);
    const Vector operator *(float c, const Vector&v);
    const Vector operator /(const Vector& v, float c);

    void operator +=(Vector& v1, const Vector& v2);
    void operator -=(Vector& v1, const Vector& v2);
    void operator *=(Vector& v, float c);
    void operator /=(Vector& v, float c);

    const float hsum(__m128 v);
    const float dot(const Vector& v1, const Vector& v2);
    const float norm(const Vector& v);
    const Vector normalize(const Vector& v);

    const bool operator ==(const Vector& v1, const Vector& v2);
    std::ostream& operator <<(std::ostream& os, const Vector& v);
}

#endif // VECTOR_H_INCLUDED
