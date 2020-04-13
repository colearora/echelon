#include "inc/vector.h"
#include <cassert>

namespace la {

Vector::Vector(int n) {
    assert(n > 0);
    _n = n;
    _ep = new float[n];
}

Vector::Vector(int n, float initVal) : Vector(n) {
    for (int i = 0; i < _n; ++i) {
        _ep[i] = initVal;
    }
}

Vector::Vector(std::initializer_list<float> list) : Vector(list.size()) {
    int i = 0;
    for (float val : list) {
        _ep[i++] = val;
    }
}

Vector::Vector(const Vector& v) : Vector(v._n) {
    for (int i = 0; i < _n; ++i) {
        _ep[i] = v[i];
    }
}

Vector::~Vector() {
    delete[] _ep;
}

Vector& Vector::operator=(const Vector& v) {
    assert(_n == v._n);
    for (int i = 0; i < _n; ++i) {
        _ep[i] = v[i];
    }
    return *this;
}

Vector& Vector::operator+=(const Vector& v) {
    assert(_n == v._n);
    for (int i = 0; i < _n; ++i) {
        _ep[i] += v[i];
    }
    return *this;
}

Vector& Vector::operator-=(const Vector& v) {
    assert(_n == v._n);
    for (int i = 0; i < _n; ++i) {
        _ep[i] -= v[i];
    }
    return *this;
}

Vector& Vector::operator*=(float x) {
    for (int i = 0; i < _n; ++i) {
        _ep[i] *= x;
    }
    return *this;
}

float& Vector::operator[](int i) {
    assert(i >= 0 && i < _n);
    return _ep[i];
}

const float& Vector::operator[](int i) const {
    assert(i >= 0 && i < _n);
    return _ep[i];
}

float* Vector::begin() {
    return _ep;
}

const float* Vector::begin() const {
    return _ep;
}

float* Vector::end() {
    return _ep + _n;
}

const float* Vector::end() const {
    return _ep + _n;
}

int Vector::dim() const {
    return _n;
}

bool operator==(const Vector& v, const Vector& w) {
    if (&v == &w) {
        return true;
    } else if (v.dim() != w.dim()) {
        return false;
    }
    for (int i = 0, n = v.dim(); i < n; ++i) {
        if (v[i] != w[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Vector& v, const Vector& w) {
    return !(v == w);
}

Vector operator+(const Vector& v, const Vector& w) {
    return Vector(v) += w;
}

Vector operator-(const Vector& v, const Vector& w) {
    return Vector(v) -= w;
}

Vector operator*(const Vector& v, float x) {
    return Vector(v) *= x;
}

Vector operator*(float x, const Vector& v) {
    return Vector(v) *= x;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(";
    for (int i = 0; i < v.dim(); ++i) {
        os << (i > 0 ? ", " : "") << v[i];
    }
    os << ")";
    return os;
}

}  // namespace la