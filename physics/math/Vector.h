#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "Eigen/Core"
#include "bits/stdc++.h"

#define EQUALITY_THRESHOLD 1e-10

namespace PMath{
    class Vector{
        private:
            Eigen::Vector4d vec;
        public:
            Vector(double x, double y, double z = 0.0, double w = 0.0){
                this->vec = Eigen::Vector4d(x, y, z, w);
            }

            const double norm() const{
                return this->vec.norm();
            }

            void normalize(){
                this->vec.normalize();
            }

            const double dot(const Vector& v) const{
                return this->vec.dot(v.vec);
            }

            friend const Vector operator -(const Vector& v);

            friend const Vector operator +(const Vector& v1, const Vector& v2);
            friend const Vector operator -(const Vector& v1, const Vector& v2);
            friend const Vector operator *(double c, const Vector& v);
            friend const Vector operator /(const Vector& v, double c);

            friend void operator +=(Vector& v1, const Vector& v2);
            friend void operator -=(Vector& v1, const Vector& v2);
            friend void operator *=(Vector& v, double c);
            friend void operator /=(Vector& v, double c);

            friend const bool operator ==(const Vector& v1, const Vector& v2);
            friend std::ostream& operator <<(std::ostream& os, const Vector& v);
    };

    inline const Vector operator -(const Vector& v){
        Vector res(0, 0, 0, 0);
        res.vec = -v.vec;
        return res;
    }

    inline const Vector operator +(const Vector& v1, const Vector& v2){
        Vector v(0, 0, 0, 0);
        v.vec = v1.vec + v2.vec;
        return v;
    }

    inline const Vector operator -(const Vector& v1, const Vector& v2){
        Vector v(0, 0, 0, 0);
        v.vec = v1.vec - v2.vec;
        return v;
    }

    inline const Vector operator *(double c, const Vector& v){
        Vector res(0, 0, 0, 0);
        res.vec = c * v.vec;
        return res;
    }

    inline const Vector operator /(const Vector& v, double c){
        Vector res(0, 0, 0, 0);
        res.vec = v.vec/c;
        return res;
    }

    inline void operator +=(Vector& v1, const Vector& v2){
        v1.vec += v2.vec;
    }

    inline void operator -=(Vector& v1, const Vector& v2){
        v1.vec -= v2.vec;
    }

    inline void operator *=(Vector& v, double c){
        v.vec *= c;
    }

    inline void operator /=(Vector& v, double c){
        v.vec /= c;
    }

    inline const bool operator ==(const Vector& v1, const Vector& v2){
        return (v1.vec - v2.vec).norm() <= EQUALITY_THRESHOLD;
    }

    inline std::ostream& operator <<(std::ostream& os, const Vector& v){
        return os << v.vec;
    }

}

#endif // VECTOR_H_INCLUDED
