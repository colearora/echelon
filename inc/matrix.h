#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include <iostream>
#include <initializer_list>
#include <cassert>
#include <limits>

namespace la 
{

/**
 * Matrix: a container that encapsulates a rectangular grid of
 * floating-point values.
 */
class Matrix 
{
public:
    Matrix(int m, int n);
    Matrix(int m, int n, float initVal);
    Matrix(const Matrix& A);
    ~Matrix();

    // Static factory methods
    static Matrix fromRows(std::initializer_list<std::initializer_list<float>> rows);
    static Matrix fromCols(std::initializer_list<std::initializer_list<float>> cols);

    Matrix& operator=(const Matrix& A);
    float& operator()(int i, int j) {checkBounds(i, j); return _rowPtr[i][j];}
    const float& operator()(int i, int j) const {checkBounds(i, j); return _rowPtr[i][j];}

    int rows() const {return _m;}
    int cols() const {return _n;}
    std::pair<int, int> size() const {return {_m, _n};}
    bool isSquare() const {return _m == _n;}
    bool isVector() const {return _m == 1 || _n == 1;}

    // Elementary row operations
    void scaleRow(int i, float f);
    void swapRows(int i1, int i2);
    void replaceRow(int i1, int i2, float f);

private:
    void checkBounds(int i, int j) const {checkRowBounds(i); checkColumnBounds(j);}
    void checkRowBounds(int i) const {assert(i >= 0 && i < _m);}
    void checkColumnBounds(int j) const {assert(j >= 0 && j < _n);}

    int _m, _n;
    float** _rowPtr;
};

std::ostream& operator<<(std::ostream& os, const Matrix& A);
bool operator==(const Matrix& A, const Matrix& B);
bool operator!=(const Matrix& A, const Matrix& B);

bool approxEqual(const Matrix& A, const Matrix& B);
Matrix round(const Matrix& A, float epsilon = std::numeric_limits<float>::epsilon());

// Matrix operations
float determinant(const Matrix& A);
Matrix inverse(const Matrix& A);
Matrix adjugate(const Matrix& A);
Matrix transpose(const Matrix& A);

}  // namespace la

#endif