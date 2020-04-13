#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include "inc/vector.h"
#include <utility>
#include <initializer_list>
#include <iostream>

namespace la {

/**
 * Matrix: represents a two-dimensional (m x n) grid of floating-point values.
 */
class Matrix {
public:
    Matrix(int m, int n);
    Matrix(int m, int n, float initVal);
    Matrix(std::initializer_list<Vector> clist);
    Matrix(std::initializer_list<std::initializer_list<float>> rlist);
    Matrix(const Matrix& A);
    ~Matrix();

    Matrix& operator=(const Matrix& A);
    Vector& operator[](int j);
    const Vector& operator[](int j) const;

    Vector* begin();
    const Vector* begin() const;
    Vector* end();
    const Vector* end() const;

    int rows() const;
    int cols() const;

    static Matrix identity(int n);

private:
    int _m, _n;
    void* _bp;    // pointer to first byte of first column
    Vector* _cp;  // pointer to first column
};

bool operator==(const Matrix& A, const Matrix& B);
bool operator!=(const Matrix& A, const Matrix& B);
std::ostream& operator<<(std::ostream& os, const Matrix& A);

}  // namespace la

#endif
