#include "inc/matrix.h"
#include "inc/util.h"

#include <cassert>
#include <utility>
#include <iostream>
#include <iomanip>
#include <cmath>

namespace la
{

Matrix::Matrix(int m, int n)
: _m{m}, _n{n}
{
    assert(m > 0 && n > 0);
    _rowPtr = new float*[m];
    for (int i = 0; i < m; ++i)
    {
        _rowPtr[i] = new float[n];
    }
}

Matrix::Matrix(int m, int n, float initVal)
: Matrix(m, n)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            _rowPtr[i][j] = initVal;
        }
    }
}

Matrix::Matrix(const Matrix& A)
: _m{A.rows()}, _n{A.cols()}
{
    _rowPtr = new float*[_m];
    for (int i = 0; i < _m; ++i)
    {
        _rowPtr[i] = new float[_n];
        for (int j = 0; j < _n; ++j)
        {
            _rowPtr[i][j] = A(i, j);
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < _m; ++i)
    {
        delete[] _rowPtr[i];
    }
    delete[] _rowPtr;
}

Matrix Matrix::fromRows(std::initializer_list<std::initializer_list<float>> rows)
{
    assert(rows.size() > 0);
    Matrix A(rows.size(), rows.begin()->size());
    int i = 0;
    for (auto row : rows)
    {
        int j = 0;
        for (float entry : row)
        {
            A(i, j) = entry;
            ++j;
        }
        ++i;
    }
    return A;
}

Matrix Matrix::fromCols(std::initializer_list<std::initializer_list<float>> cols)
{
    return transpose(fromRows(cols));
}

Matrix& Matrix::operator=(const Matrix& A)
{
    assert(_m == A.rows() && _n == A.cols());
    for (int i = 0; i < _m; ++i)
    {
        for (int j = 0; j < _n; ++j)
        {
            _rowPtr[i][j] = A(i, j);
        }
    }
    return *this;
}

/* scaleRow: elementary row operation. */
void Matrix::scaleRow(int i, float f)
{
    checkRowBounds(i);
    for (int j = 0; j < _n; ++j)
    {
        _rowPtr[i][j] *= f;
    }
}

/* swapRows: elementary row operation. */
void Matrix::swapRows(int i1, int i2)
{
    checkRowBounds(i1);
    checkRowBounds(i2);
    std::swap(_rowPtr[i1], _rowPtr[i2]);
}

/* replaceRow: elementary row operation; adds to row i1 an f-scaled row i2 */
void Matrix::replaceRow(int i1, int i2, float f)
{
    checkRowBounds(i1);
    checkRowBounds(i2);
    for (int j = 0; j < _n; ++j)
    {
        _rowPtr[i1][j] += f * _rowPtr[i2][j];
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& A)
{
    std::ios_base::fmtflags f = os.flags();  // save ostream state
    os << std::defaultfloat;
    for (int i = 0; i < A.rows(); ++i)
    {
        for (int j = 0; j < A.cols(); ++j)
        {
            os << std::setw(18) << std::setprecision(8) << A(i, j);
        }
        os << '\n';
    }
    os.flags(f);  // restore ostream state
    return os;
}

bool operator==(const Matrix& A, const Matrix& B)
{
    if (A.size() != B.size())
    {
        return false;
    }
    for (int i = 0; i < A.rows(); ++i)
    {
        for (int j = 0; j < A.cols(); ++j)
        {
            if (A(i, j) != B(i, j))
            {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& A, const Matrix& B)
{
    return !(A == B);
}

bool approxEqual(const Matrix& A, const Matrix& B)
{
    if (A.size() != B.size())
    {
        return false;
    }
    for (int i = 0; i < A.rows(); ++i) 
    {
        for (int j = 0; j < A.cols(); ++j)
        {
            if (!approxEqual(A(i, j), B(i, j)))
            {
                return false;
            }
        }
    }
    return true;
}

Matrix round(const Matrix& A, float epsilon)
{
    Matrix B(A.rows(), A.cols());
    for (int i = 0; i < A.rows(); ++i)
    {
        for (int j = 0; j < A.cols(); ++j)
        {
            float actual = A(i, j);
            float rounded = std::round(actual);
            B(i, j) = (approxEqual(actual, rounded) ? rounded : actual);
        }
    }
    return B;
}

float determinant(const Matrix& A)
{
    // TODO: implement
    return 0.0F;
}

Matrix inverse(const Matrix& A)
{
    // TODO: implement
    return A;
}

Matrix adjugate(const Matrix& A)
{
    // TODO: implement
    return A;
}

Matrix transpose(const Matrix& A)
{
    Matrix B(A.cols(), A.rows());
    for (int i = 0; i < A.rows(); ++i)
    {
        for (int j = 0; j < A.cols(); ++j)
        {
            B(j, i) = A(i, j);
        }
    }
    return B;
}

}  // namespace la