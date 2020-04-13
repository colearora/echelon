#include "inc/matrix.h"
#include <cassert>

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

Matrix::Matrix(std::initializer_list<Vector> clist)
        : Matrix(clist.begin()->dim(), clist.size()) {
    int j = 0;
    for (const Vector& c : clist) {
        _cp[j++] = c;
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<float>> rlist)
        : Matrix(rlist.size(), rlist.begin()->size()) {
    int i = 0;
    for (auto r : rlist) {
        int j = 0;
        for (float val : r) {
            _cp[j++][i] = val;
        }
        ++i;
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

Matrix Matrix::identity(int n) {
    Matrix I(n, n, 0.0F);
    for (int j = 0; j < n; ++j) {
        I[n][n] = 1.0F;
    }
    return I;
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

std::ostream& operator<<(std::ostream& os, const Matrix& A) {
    for (int i = 0, m = A.rows(); i < m; ++i) {
        os << (i == 0 ? "((" : " (");
        for (int j = 0, n = A.cols(); j < n; ++j) {
            os << (j > 0 ? ", " : "") << A[j][i];
        }
        os << (i == m - 1 ? "))\n" : ")\n");
    }
    return os;
}

}  // namespace la
