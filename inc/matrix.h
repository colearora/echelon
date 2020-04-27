#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include "inc/vector.h"
#include <utility>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <set>

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
    Matrix& operator+=(const Matrix& A);
    Matrix& operator-=(const Matrix& A);
    Matrix& operator*=(float f);
    Vector& operator[](int j);              // column accessor
    const Vector& operator[](int j) const;  // column accessor

    Vector* begin();
    const Vector* begin() const;
    Vector* end();
    const Vector* end() const;

    int rows() const;
    int cols() const;

    // Factories:
    static Matrix fromRows(std::initializer_list<Vector> rlist);
    static Matrix fromCols(std::initializer_list<Vector> clist);
    static Matrix fromDiag(const Vector& d);
    static Matrix fromParts(const Matrix& A, const Vector& b);
    static Matrix fromParts(const Matrix& A, const Matrix& B);
    static Matrix identity(int n);
    static Matrix random(int m, int n);
    static Matrix random(int m, int n, float lo, float hi);
    static Matrix whitelist(const Matrix& A, std::set<int> rs, std::set<int> cs);
    static Matrix blacklist(const Matrix& A, std::set<int> rs, std::set<int> cs);

private:
    int _m;       // number of rows
    int _n;       // number of columns
    void* _bp;    // pointer to first byte of first column
    Vector* _cp;  // pointer to first column
};

bool operator==(const Matrix& A, const Matrix& B);
bool operator!=(const Matrix& A, const Matrix& B);
Matrix operator+(const Matrix& A, const Matrix& B);
Matrix operator-(const Matrix& A, const Matrix& B);
Matrix operator*(const Matrix& A, float f);
Matrix operator*(float f, const Matrix& A);
Vector operator*(const Matrix& A, const Vector& x);
Matrix operator*(const Matrix& A, const Matrix& B);
std::ostream& operator<<(std::ostream& os, const Matrix& A);

Matrix round(const Matrix& A, float epsilon = std::numeric_limits<float>::epsilon());
bool approxEqual(const Matrix& A, const Matrix& B,
                 float epsilon = std::numeric_limits<float>::epsilon());

bool isSquare(const Matrix& A);
bool isInvertible(const Matrix& A);

Matrix pow(const Matrix& A, unsigned int k);
Matrix transpose(const Matrix& A);
float det(const Matrix& A);
Matrix inverse(const Matrix& A);

}  // namespace la

#endif
