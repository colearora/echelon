#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include "inc/vector.h"
#include <utility>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace la {

/**
 * Matrix: represents a two-dimensional (m x n) grid of floating-point values.
 */
class Matrix {
public:
    Matrix(int m, int n);
    Matrix(int m, int n, float initVal);
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

    static Matrix fromRows(std::initializer_list<Vector> rlist);
    static Matrix fromCols(std::initializer_list<Vector> clist);
    static Matrix identity(int n);
    static Matrix diagonal(const Vector& d);

private:
    int _m;       // number of rows
    int _n;       // number of columns
    void* _bp;    // pointer to first byte of first column
    Vector* _cp;  // pointer to first column
};

bool operator==(const Matrix& A, const Matrix& B);
bool operator!=(const Matrix& A, const Matrix& B);
Vector operator*(const Matrix& A, const Vector& x);
Vector& operator*=(Matrix& A, Vector& x);
std::ostream& operator<<(std::ostream& os, const Matrix& A);

Matrix round(const Matrix& A, float epsilon = std::numeric_limits<float>::epsilon());
bool approxEqual(const Matrix& A, const Matrix& B,
                 float epsilon = std::numeric_limits<float>::epsilon());

}  // namespace la

#endif
