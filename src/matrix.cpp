#include "inc/matrix.h"
#include "inc/util.h"
#include "inc/gauss.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace la
{

Matrix::Matrix(int m, int n)
{
    assert(m > 0 && n > 0);
    _m = m;
    _n = n;

    // Allocate enough memory for an array of n (column) Vectors.
    _bp = operator new[](_n * sizeof(Vector));

    // Make _cp point to it so it can be treated as a Vector array.
    _cp = static_cast<Vector*>(_bp);

    // Construct the Vectors in the memory using "placement new".
    for (int j = 0; j < _n; ++j)
    {
        new (_cp + j) Vector(_m);
    }
}

Matrix::Matrix(int m, int n, float initVal)
: Matrix(m, n)
{
    for (int j = 0; j < _n; ++j)
    {
        for (int i = 0; i < _m; ++i)
        {
            _cp[j][i] = initVal;
        }
    }
}

Matrix::Matrix(const Matrix& A)
: Matrix(A._m, A._n)
{
    for (int j = 0; j < _n; ++j)
    {
        _cp[j] = A[j];
    }
}

Matrix::~Matrix()
{
    // Destruct the Vectors in reverse order of construction.
    for (int j = _n - 1; j >= 0; --j)
    {
        _cp[j].~Vector();
    }

    // Deallocate the raw memory.
    operator delete[](_bp);
}

Matrix& Matrix::operator=(const Matrix& A)
{
    assert(_m == A._m && _n == A._n);
    for (int j = 0; j < _n; ++j)
    {
        _cp[j] = A[j];
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& A)
{
    assert(_m == A._m && _n == A._n);
    for (int j = 0; j < _n; ++j)
    {
        _cp[j] += A[j];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& A)
{
    assert(_m == A._m && _n == A._n);
    for (int j = 0; j < _n; ++j)
    {
        _cp[j] -= A[j];
    }
    return *this;
}

Matrix& Matrix::operator*=(float f)
{
    for (int j = 0; j < _n; ++j)
    {
        _cp[j] *= f;
    }
    return *this;
}

Vector& Matrix::operator[](int j)
{
    assert(j >= 0 && j < _n);
    return _cp[j];
}

const Vector& Matrix::operator[](int j) const
{
    assert(j >= 0 && j < _n);
    return _cp[j];
}

Vector* Matrix::begin()
{
    return _cp;
}

const Vector* Matrix::begin() const
{
    return _cp;
}

Vector* Matrix::end()
{
    return _cp + _n;
}

const Vector* Matrix::end() const
{
    return _cp + _n;
}

int Matrix::rows() const
{
    return _m;
}

int Matrix::cols() const
{
    return _n;
}

Matrix Matrix::fromRows(std::initializer_list<Vector> rlist)
{
    assert(rlist.size() > 0);
    int m = rlist.size();
    int n = rlist.begin()->size();
    la::Matrix A(m, n);
    int i = 0;
    for (const Vector& r : rlist)
    {
        int j = 0;
        for (float entry : r)
        {
            A[j++][i] = entry;
        }
        ++i;
    }
    return A;
}

Matrix Matrix::fromCols(std::initializer_list<Vector> clist)
{
    assert(clist.size() > 0);
    int m = clist.begin()->size();
    int n = clist.size();
    la::Matrix A(m, n);
    int j = 0;
    for (const Vector& c : clist)
    {
        A[j++] = c;
    }
    return A;
}

Matrix Matrix::fromDiag(const Vector& d)
{
    int n = d.size();
    Matrix D(n, n, 0.0F);
    for (int j = 0; j < n; ++j)
    {
        D[j][j] = d[j];
    }
    return D;
}

Matrix Matrix::identity(int n)
{
    return fromDiag(Vector(n, 1.0F));
}

Matrix Matrix::random(int m, int n)
{
    Matrix R(m, n);
    for (Vector& c : R)
    {
        c = Vector::random(m);
    }
    return R;
}

Matrix Matrix::random(int m, int n, float lo, float hi)
{
    assert(hi >= lo);
    return (hi - lo) * random(m, n) + Matrix(m, n, lo);
}

bool operator==(const Matrix& A, const Matrix& B)
{
    if (&A == &B)
    {
        return true;
    }
    if (A.rows() != B.rows() || A.cols() != B.cols())
    {
        return false;
    }
    for (int j = 0, n = A.cols(); j < n; ++j)
    {
        if (A[j] != B[j])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& A, const Matrix& B)
{
    return !(A == B);
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
    return Matrix(A) += B;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
    return Matrix(A) -= B;
}

Matrix operator*(const Matrix& A, float f)
{
    return Matrix(A) *= f;
}

Matrix operator*(float f, const Matrix& A)
{
    return Matrix(A) *= f;
}

Vector operator*(const Matrix& A, const Vector& x)
{
    assert(A.cols() == x.size());
    Vector b(A.rows(), 0.0F);
    for (int j = 0; j < A.cols(); ++j)
    {
        b += x[j] * A[j];
    }
    return b;
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
    assert(A.cols() == B.rows());
    Matrix M(A.rows(), B.cols());
    for (int j = 0; j < B.cols(); ++j)
    {
        M[j] = A * B[j];
    }
    return M;
}

std::ostream& operator<<(std::ostream& os, const Matrix& A)
{
    int maxw[A.cols()];  // max width of default-formatted floats in A by column
    std::ostringstream oss;
    for (int j = 0; j < A.cols(); ++j)
    {
        maxw[j] = 0;
        for (float entry : A[j])
        {
            oss.str("");
            oss << entry;
            int w = oss.str().size();
            maxw[j] = std::max(maxw[j], w);
        }
    }
    for (int i = 0, m = A.rows(); i < m; ++i)
    {
        os << (i == 0 ? "((" : " (");
        for (int j = 0, n = A.cols(); j < n; ++j)
        {
            os << (j > 0 ? ", " : "") << std::setw(maxw[j]) << A[j][i];
        }
        os << (i == m - 1 ? "))\n" : ")\n");
    }
    return os;
}

Matrix round(const Matrix& A, float epsilon)
{
    Matrix B(A.rows(), A.cols());
    for (int j = 0; j < B.cols(); ++j)
    {
        B[j] = round(A[j], epsilon);
    }
    return B;
}

bool approxEqual(const Matrix& A, const Matrix& B, float epsilon)
{
    if (&A == &B)
    {
        return true;
    }
    if (A.rows() != B.rows() || A.cols() != B.cols())
    {
        return false;
    }
    for (int j = 0; j < A.cols(); ++j)
    {
        if (!approxEqual(A[j], B[j], epsilon))
        {
            return false;
        }
    }
    return true;
}

Matrix augment(const Matrix& A, const Vector& b)
{
    return augment(A, Matrix::fromCols({b}));
}

Matrix augment(const Matrix& A, const Matrix& B)
{
    assert(A.rows() == B.rows());
    int m = A.rows();
    int n = A.cols() + B.cols();
    Matrix aug(m, n);
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < m; ++i)
        {
            aug[j][i] = (j < A.cols()) ? A[j][i] : B[j - A.cols()][i];
        }
    }
    return aug;
}

Matrix deleteRow(const Matrix& A, int i)
{
    assert(i >= 0 && i < A.rows());
    Matrix B(A.rows() - 1, A.cols());
    int iB = 0;
    for (int iA = 0; iA < A.rows(); ++iA)
    {
        if (iA == i)
        {
            continue;
        }
        for (int j = 0; j < A.cols(); ++j)
        {
            B[j][iB] = A[j][iA];
        }
        ++iB;
    }
    return B;
}

Matrix deleteCol(const Matrix& A, int j)
{
    assert(j >= 0 && j < A.cols());
    Matrix B(A.rows(), A.cols() - 1);
    int jB = 0;
    for (int jA = 0; jA < A.cols(); ++jA)
    {
        if (jA == j)
        {
            continue;
        }
        B[jB] = A[jA];
        ++jB;
    }
    return B;
}

Matrix deleteRowAndCol(const Matrix& A, int i, int j)
{
    assert(i >= 0 && i < A.rows() && j >= 0 && j < A.cols());
    Matrix B(A.rows() - 1, A.cols() - 1);
    int jB = 0;
    for (int jA = 0; jA < A.cols(); ++jA)
    {
        if (jA == j)
        {
            continue;
        }
        int iB = 0;
        for (int iA = 0; iA < A.rows(); ++iA)
        {
            if (iA == i)
            {
                continue;
            }
            B[jB][iB] = A[jA][iA];
            ++iB;
        }
        ++jB;
    }
    return B;
}

Matrix partition(const Matrix& A, std::pair<int, int> topLeft,
                 std::pair<int, int> bottomRight)
{
    int m = bottomRight.first - topLeft.first + 1;
    int n = bottomRight.second - topLeft.second + 1;
    assert(m > 0 && m <= A.rows() && n > 0 && n <= A.cols());
    Matrix B(m, n);
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < m; ++i)
        {
            B[j][i] = A[topLeft.second + j][topLeft.first + i];
        }
    }
    return B;
}

bool isSquare(const Matrix& A)
{
    return A.rows() == A.cols();
}

bool isInvertible(const Matrix& A)
{
    Matrix temp(A.rows(), A.cols());
    return inverse(A, temp);
}

Matrix pow(const Matrix& A, unsigned int k)
{
    return (k == 0) ? Matrix::identity(A.rows()) : A * pow(A, k - 1);
}

Matrix transpose(const Matrix& A)
{
    Matrix T(A.cols(), A.rows());
    for (int j = 0; j < A.cols(); ++j)
    {
        // Set jth row of T equal to the jth column of A.
        for (int i = 0; i < A.rows(); ++i)
        {
            T[i][j] = A[j][i];
        }
    }
    return T;
}

/**
 * Attempts to invert A.
 * If A is invertible, writes inverse to AInv and returns true,
 * otherwise returns false.
 */
bool inverse(const Matrix& A, Matrix& AInv)
{
    assert(A.rows() == AInv.rows() && A.cols() == AInv.cols());
    if (!isSquare(A))
    {
        return false;
    }

    // By the Invertible Matrix Theorem, A is invertible iff A ~ I.
    // In that case the row operations that reduce A to I convert I to A's inverse.
    // Thus, strategy is to reduce [A I] to reduced echelon form.
    int n = A.rows();
    Matrix I = Matrix::identity(n);
    Matrix aug = augment(A, I);
    eliminate(aug, partialPivotSelector);
    if (approxEqual(partition(aug, {0, 0}, {n - 1, n - 1}), I))
    {
        AInv = partition(aug, {0, n}, {n - 1, 2 * n - 1});
        return true;
    }
    else
    {
        return false;
    }
}

float det(const Matrix& A)
{
    // TODO
    return 0.0F;
}

}  // namespace la
