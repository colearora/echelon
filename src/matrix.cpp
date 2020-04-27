#include "inc/matrix.h"
#include "inc/util.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace la {

Matrix::Matrix(int m, int n) {
    assert(m > 0 && n > 0);
    _m = m;
    _n = n;

    // Allocate enough memory for an array of n (column) Vectors.
    _bp = operator new[](_n * sizeof(Vector));

    // Make _cp point to it so it can be treated as a Vector array.
    _cp = static_cast<Vector*>(_bp);

    // Construct the Vectors in the memory using "placement new".
    for (int j = 0; j < _n; ++j) {
        new (_cp + j) Vector(_m);
    }
}

Matrix::Matrix(int m, int n, float initVal) : Matrix(m, n) {
    for (int j = 0; j < _n; ++j) {
        for (int i = 0; i < _m; ++i) {
            _cp[j][i] = initVal;
        }
    }
}

Matrix::Matrix(const Matrix& A) : Matrix(A._m, A._n) {
    for (int j = 0; j < _n; ++j) {
        _cp[j] = A[j];
    }
}

Matrix::~Matrix() {
    // Destruct the Vectors in reverse order of construction.
    for (int j = _n - 1; j >= 0; --j) {
        _cp[j].~Vector();
    }

    // Deallocate the raw memory.
    operator delete[](_bp);
}

Matrix& Matrix::operator=(const Matrix& A) {
    assert(_m == A._m && _n == A._n);
    for (int j = 0; j < _n; ++j) {
        _cp[j] = A[j];
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& A) {
    assert(_m == A._m && _n == A._n);
    for (int j = 0; j < _n; ++j) {
        _cp[j] += A[j];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& A) {
    assert(_m == A._m && _n == A._n);
    for (int j = 0; j < _n; ++j) {
        _cp[j] -= A[j];
    }
    return *this;
}

Matrix& Matrix::operator*=(float f) {
    for (int j = 0; j < _n; ++j) {
        _cp[j] *= f;
    }
    return *this;
}

Vector& Matrix::operator[](int j) {
    assert(j >= 0 && j < _n);
    return _cp[j];
}

const Vector& Matrix::operator[](int j) const {
    assert(j >= 0 && j < _n);
    return _cp[j];
}

Vector* Matrix::begin() {
    return _cp;
}

const Vector* Matrix::begin() const {
    return _cp;
}

Vector* Matrix::end() {
    return _cp + _n;
}

const Vector* Matrix::end() const {
    return _cp + _n;
}

int Matrix::rows() const {
    return _m;
}

int Matrix::cols() const {
    return _n;
}

Matrix Matrix::fromRows(std::initializer_list<Vector> rlist) {
    assert(rlist.size() > 0);
    int m = rlist.size();
    int n = rlist.begin()->size();
    la::Matrix A(m, n);
    int i = 0;
    for (const Vector& r : rlist) {
        int j = 0;
        for (float entry : r) {
            A[j++][i] = entry;
        }
        ++i;
    }
    return A;
}

Matrix Matrix::fromCols(std::initializer_list<Vector> clist) {
    assert(clist.size() > 0);
    int m = clist.begin()->size();
    int n = clist.size();
    la::Matrix A(m, n);
    int j = 0;
    for (const Vector& c : clist) {
        A[j++] = c;
    }
    return A;
}

/* Returns the square matrix having d as main diagonal and zeros elsewhere. */
Matrix Matrix::fromDiag(const Vector& d) {
    int n = d.size();
    Matrix D(n, n, 0.0F);
    for (int j = 0; j < n; ++j) {
        D[j][j] = d[j];
    }
    return D;
}

/* Returns the augmented matrix [A b]. */
Matrix Matrix::fromParts(const Matrix& A, const Vector& b) {
    return fromParts(A, fromCols({b}));
}

/* Returns the augmented matrix [A B]. */
Matrix Matrix::fromParts(const Matrix& A, const Matrix& B) {
    assert(A.rows() == B.rows());
    int m = A.rows();
    int n = A.cols() + B.cols();
    Matrix C(m, n);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            C[j][i] = (j < A.cols()) ? A[j][i] : B[j - A.cols()][i];
        }
    }
    return C;
}

/* Returns the n x n matrix having ones on main diagonal and zeros elsewhere. */
Matrix Matrix::identity(int n) {
    return fromDiag(Vector(n, 1.0F));
}

/* Returns an m x n matrix with random entries in [0,1]. */
Matrix Matrix::random(int m, int n) {
    Matrix R(m, n);
    for (Vector& c : R) {
        c = Vector::random(m);
    }
    return R;
}

/* Returns an m x n matrix with random entries in [lo, hi]. */
Matrix Matrix::random(int m, int n, float lo, float hi) {
    assert(hi >= lo);
    return (hi - lo) * random(m, n) + Matrix(m, n, lo);
}

/** 
 * Returns the submatrix formed from A by deleting rows and columns
 * not in rs and cs respectively.
 */
Matrix Matrix::whitelist(const Matrix& A, std::set<int> rs, std::set<int> cs) {
    assert(rs.size() > 0 && rs.size() <= A.rows());
    assert(cs.size() > 0 && cs.size() <= A.cols());
    assert(*rs.begin() >= 0 && *--rs.end() < A.rows());
    assert(*cs.begin() >= 0 && *--cs.end() < A.cols());

    Matrix B(rs.size(), cs.size());
    int jB = 0;
    for (int jA = 0; jA < A.cols(); ++jA) {
        if (cs.find(jA) == cs.end()) {
            continue;  // column not in scope for inclusion
        }
        int iB = 0;
        for (int iA = 0; iA < A.rows(); ++iA) {
            if (rs.find(iA) == rs.end()) {
                continue;  // (iA, jA)-entry not in scope for inclusion
            }
            B[jB][iB++] = A[jA][iA];
        }
        ++jB;
    }
    return B;    
}

/** 
 * Returns the submatrix formed from A by deleting rows and columns
 * in rs and cs respectively.
 */
Matrix Matrix::blacklist(const Matrix& A, std::set<int> rs, std::set<int> cs) {
    assert(rs.size() < A.rows() && cs.size() < A.cols());
    assert(*rs.begin() >= 0 && *--rs.end() < A.rows());
    assert(*cs.begin() >= 0 && *--cs.end() < A.cols());

    Matrix B(A.rows() - rs.size(), A.cols() - cs.size());
    int jB = 0;
    for (int jA = 0; jA < A.cols(); ++jA) {
        if (cs.find(jA) != cs.end()) {
            continue;  // column in scope for exclusion
        }
        int iB = 0;
        for (int iA = 0; iA < A.rows(); ++iA) {
            if (rs.find(iA) != rs.end()) {
                continue;  // (iA, jA)-entry in scope for exclusion
            }
            B[jB][iB++] = A[jA][iA];
        }
        ++jB;
    }
    return B;
}

bool operator==(const Matrix& A, const Matrix& B) {
    if (&A == &B) {
        return true;
    } else if (A.rows() != B.rows() || A.cols() != B.cols()) {
        return false;
    }
    for (int j = 0, n = A.cols(); j < n; ++j) {
        if (A[j] != B[j]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& A, const Matrix& B) {
    return !(A == B);
}

Matrix operator+(const Matrix& A, const Matrix& B) {
    return Matrix(A) += B;
}

Matrix operator-(const Matrix& A, const Matrix& B) {
    return Matrix(A) -= B;
}

Matrix operator*(const Matrix& A, float f) {
    return Matrix(A) *= f;
}

Matrix operator*(float f, const Matrix& A) {
    return Matrix(A) *= f;
}

Vector operator*(const Matrix& A, const Vector& x) {
    assert(A.cols() == x.size());
    Vector b(A.rows(), 0.0F);
    for (int j = 0; j < A.cols(); ++j) {
        b += x[j] * A[j];
    }
    return b;
}

Matrix operator*(const Matrix& A, const Matrix& B) {
    assert(A.cols() == B.rows());
    Matrix M(A.rows(), B.cols());
    for (int j = 0; j < B.cols(); ++j) {
        M[j] = A * B[j];
    }
    return M;
}

std::ostream& operator<<(std::ostream& os, const Matrix& A) {
    int maxw[A.cols()];  // max width of default-formatted floats in A by column
    std::ostringstream oss;
    for (int j = 0; j < A.cols(); ++j) {
        maxw[j] = 0;
        for (float entry : A[j]) {
            oss.str("");
            oss << entry;
            int w = oss.str().size();
            maxw[j] = std::max(maxw[j], w);
        }
    }
    for (int i = 0, m = A.rows(); i < m; ++i) {
        os << (i == 0 ? "((" : " (");
        for (int j = 0, n = A.cols(); j < n; ++j) {
            os << (j > 0 ? ", " : "") << std::setw(maxw[j]) << A[j][i];
        }
        os << (i == m - 1 ? "))\n" : ")\n");
    }
    return os;
}

Matrix round(const Matrix& A, float epsilon) {
    Matrix B(A.rows(), A.cols());
    for (int j = 0; j < B.cols(); ++j) {
        B[j] = round(A[j], epsilon);
    }
    return B;
}

bool approxEqual(const Matrix& A, const Matrix& B, float epsilon) {
    if (A.rows() != B.rows() || A.cols() != B.cols()) {
        return false;
    }
    for (int j = 0; j < A.cols(); ++j) {
        if (!approxEqual(A[j], B[j], epsilon)) {
            return false;
        }
    }
    return true;
}

bool isSquare(const Matrix& A) {
    return A.rows() == A.cols();
}

/* Returns true if A is invertible (non-singular), false otherwise. */
bool isInvertible(const Matrix& A) {
    return isSquare(A) && !approxEqual(det(A), 0.0F);
}

/* Returns the kth power of square matrix A. */
Matrix pow(const Matrix& A, unsigned int k) {
    return (k == 0) ? Matrix::identity(A.rows()) : A * pow(A, k - 1);
}

Matrix transpose(const Matrix& A) {
    Matrix T(A.cols(), A.rows());
    for (int j = 0; j < A.cols(); ++j) {
        // Set jth row of T equal to the jth column of A.
        for (int i = 0; i < A.rows(); ++i) {
            T[i][j] = A[j][i];
        }
    }
    return T;
}

/**
 * Returns the determinant of square matrix A. 
 * Computed using Laplace (cofactor) expansion.
 **/
float det(const Matrix& A) {
    assert(isSquare(A));
    if (A.rows() == 1) {
        return A[0][0];
    } else if (A.rows() == 2) {
        return (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
    }

    // Identify the row (i) with the most zeros.
    // Expanding this row requires the least work.
    int i = 0;
    int maxZeros = 0;
    for (int k = 0; k < A.rows(); ++k) {
        int zeros = 0;
        for (int j = 0; j < A.cols(); ++j) {
            if (A[j][k] == 0.0F) {
                ++zeros;
            }
        }
        if (zeros > maxZeros) {
            maxZeros = zeros;
            i = k;
        }
    }

    // Expand the ith row.
    float sum = 0.0F;
    for (int j = 0; j < A.cols(); ++j) {
        if (A[j][i] == 0.0F) {
            continue;  // no need to compute cofactor -- would be scaled by 0
        }
        float minor = det(Matrix::blacklist(A, {i}, {j}));
        float cofactor = std::pow(-1.0F, i + j) * minor;
        sum += A[j][i] * cofactor;
    }
    return sum;
}

/* Returns the matrix inverse of (assumed invertible) matrix A. */
Matrix inverse(const Matrix& A) {
    // TODO
    return A;
}

}  // namespace la
