#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "nmmintrin.h"
#include "Vector.h"
#include <ostream>
#include <vector>
#include <cassert>

#define EQUALITY_THRESHOLD 1e-10


namespace PMath {
	template <typename T>
	struct Matrix {
		std::vector<T> rows;

		Matrix() {
			this->rows = std::vector<T>();
		}

		void AddRow(T row) {
			rows.emplace_back(row);
		}

		void operator=(const Matrix<T>& other) {
			this->rows = other.rows;
		}
	};

	typedef struct Matrix<Vector> PhysicsMatrix;

	template<typename T>
	std::ostream& operator <<(std::ostream& os, const Matrix<T>& M) {
		for (T row : M.rows)
			os << "[" << row << "]\n";
		return os;
	}

	template<typename T>
	Matrix<T> operator +(const Matrix<T>& A, const Matrix<T>& B) {
		assert(A.rows.size() == B.rows.size());
		Matrix<T> C; 

		int size = A.rows.size();
		for (int i = 0; i < size; i++) {
			C.AddRow(A.rows[i] + B.rows[i]);
		}

		return C;
	}

	template<typename T>
	Matrix<T> operator -(const Matrix<T>& A, const Matrix<T>& B) {
		assert(A.rows.size() == B.rows.size());
		Matrix<T> C;

		int size = A.rows.size();
		for (int i = 0; i < size; i++) {
			C.AddRow(A.rows[i] - B.rows[i]);
		}

		return C;
	}
	
	template<typename T>
	Matrix<T> operator *(const float c, const Matrix<T>& A) {
		Matrix<T> C;

		int size = A.rows.size();
		for (int i = 0; i < size; i++) {
			C.AddRow(c * B.rows[i]);
		}

		return C;
	}

	template<typename T>
	Matrix<T> operator *(const Matrix<T>& A, const float c) {
		Matrix<T> C;

		int size = A.rows.size();
		for (int i = 0; i < size; i++) {
			C.AddRow(c * B.rows[i]);
		}

		return C;
	}

	template<typename T>
	Matrix<T> operator /(const Matrix<T>& A, const float c) {
		Matrix<T> C;

		int size = A.rows.size();
		for (int i = 0; i < size; i++) {
			C.AddRow(c * B.rows[i]);
		}

		return C;
	}

	template<typename T>
	void operator +=(const Matrix<T>& A, const Matrix<T>& B) {
		A = A + B;
	}
	
	template<typename T>
	void operator -=(const Matrix<T>& A, const Matrix<T>& B) {
		A = A - B;
	}

	template<typename T>
	void operator *=(const Matrix<T>& A, float c) {
		A = A * c;
	}

	template<typename T>
	void operator /=(const Matrix<T>& A, float c) {
		A = A / c;
	}
}

#endif
