#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "bits/stdc++.h"

#define EQUALITY_THRESHOLD 1e-10

namespace PMath{
    class Vector{
        private:
            double vec[4];

        public:
            Vector(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0){
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
                vec[3] = w;
            }

            const double norm() const{
                double sum = 0;
                for(int i = 0 ; i < 4; i++){
                    sum += vec[i] * vec[i];
                }

                return sqrt(sum);
            }

            void set(int index, double value) {
                vec[index] = value;
            }

            double get(int index){
                return vec[index];
            }

            void normalize(){
                double norm = this->norm();
                for(int i = 0; i < 4; i++){
                    vec[i] /= norm;
                }
            }

            const double dot(const Vector& v) const{
                double result = 0;
                for(int i = 0; i < 4; i++){
                    result += v.vec[i] * this->vec[i];
                }
                return result;
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
        for(int i = 0; i < 4; i++){
            res.set(i, -v.vec[i]);
        }
        return res;
    }

    inline const Vector operator +(const Vector& v1, const Vector& v2){
        Vector v(0, 0, 0, 0);
        for(int i = 0; i < 4; i++){
            v.set(i, v1.vec[i] + v2.vec[i]);
        }
        return v;
    }

    inline const Vector operator -(const Vector& v1, const Vector& v2){
        Vector v(0, 0, 0, 0);
        for(int i = 0; i < 4; i++){
            v.set(i, v1.vec[i] - v2.vec[i]);
        }
        return v;
    }

    inline const Vector operator *(double c, const Vector& v){
        Vector res(0, 0, 0, 0);
        for(int i = 0; i < 4; i++){
            res.set(i, v.vec[i] * c);
        }
        return res;
    }

    inline const Vector operator /(const Vector& v, double c){
        Vector res(0, 0, 0, 0);
        for(int i = 0; i < 4; i++){
            res.set(i, v.vec[i] / c);
        }
        return res;
    }

    inline void operator +=(Vector& v1, const Vector& v2){
        v1 = v1 + v2;
    }

    inline void operator -=(Vector& v1, const Vector& v2){
        v1 = v1 - v2;
    }

    inline void operator *=(Vector& v, double c){
        v = c * v;
    }

    inline void operator /=(Vector& v, double c){
        v = v / c;
    }

    inline const bool operator ==(const Vector& v1, const Vector& v2){
        return (v1 - v2).norm() <= EQUALITY_THRESHOLD;
    }

    inline std::ostream& operator <<(std::ostream& os, const Vector& v){
        return os << "["<<v.vec[0]<<",\t"<<v.vec[1]<<",\t"<<v.vec[2]<<",\t"<<v.vec[3]<<"]";
    }

}

#endif // VECTOR_H_INCLUDED
