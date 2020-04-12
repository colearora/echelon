#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include "inc/vector.h"
#include <iostream>
#include <initializer_list>
#include <cassert>
#include <limits>

namespace la {

/**
 * Matrix: represents a two-dimensional grid of values.
 */
template <typename T, std::size_t m, std::size_t n>
class Matrix {
public:
    Matrix() = default;
    Matrix(T t0) {
        for (std::size_t j = 0; j < n; ++j) {
            for (std::size_t i = 0; i < m; ++i) {
                _ent[j][i] = t0;
            }
        }
    }
    Matrix(std::initializer_list<std::initializer_list<T>> rows) {
        assert(m == rows.size() && n == rows.begin()->size());
        int i = 0;
        for (auto row : rows) {
            int j = 0;
            for (T t : row) {
                _ent[j++][i] = t;  // cache-inefficient
            }
            ++i;
        }
    }

    T& operator()(int i, int j) {
        assert(i < m && j < n); 
        return _ent[j][i];
    }
    const T& operator()(int i, int j) const {
        assert(i < m && j < n); 
        return _ent[j][i];
    }
    Vector<T, m>& operator[](int j) {
        assert(j < n);
        return *reinterpret_cast<Vector<T, m>*>(_ent[j]);
    }
    const Vector<T, m>& operator[](int j) const {
        assert(j < n);
        return *reinterpret_cast<Vector<T, m>*>(_ent[j]);
    }

    std::size_t rows() const {return m;}
    std::size_t cols() const {return n;}

private:
    T _ent[n][m];  // column major
};

template <typename T, std::size_t m, std::size_t n>
std::ostream& operator<<(std::ostream& os, const Matrix<T, m, n>& A) {
    for (int i = 0; i < A.rows(); ++i) {
        os << (i == 0 ? "((" : " (");
        for (int j = 0; j < A.cols(); ++j) {
            os << (j > 0 ? ", " : "") << A(i, j);
        }
        os << (i == A.rows() - 1 ? "))\n" : ")\n");
    }
    return os;
}

}  // namespace la

#endif