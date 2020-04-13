#include "inc/vector.h"
#include <cassert>

namespace la {

Vector::Vector(std::size_t n) : _n{n}, _ent{new float[n]} {}

Vector::Vector(std::size_t n, float initVal) : Vector(n) {
    for (std::size_t i = 0; i < _n; ++i) {
        _ent[i] = initVal;
    }
}

Vector::Vector(std::initializer_list<float> list) : Vector(list.size()) {
    std::size_t i = 0; 
    for (float val : list) {
        _ent[i++] = val;
    }
}

Vector::Vector(const Vector& v) : Vector(v.dim()) {
    for (std::size_t i = 0; i < _n; ++i) {
        _ent[i] = v[i];
    }
}

Vector::~Vector() {
    delete[] _ent;
}

Vector& Vector::operator=(const Vector& v) {
    assert(dim() == v.dim());
    for (int i = 0; i < _n; ++i) {
        _ent[i] = v[i];
    }
    return *this;
}

float& Vector::operator[](std::size_t i) {
    assert(i < _n);
    return _ent[i];
}

const float& Vector::operator[](std::size_t i) const {
    assert(i < _n);
    return _ent[i];
}

std::size_t Vector::dim() const {
    return _n;
}

bool operator==(const Vector& v, const Vector& w) {
    if (&v == &w) {
        return true;
    } else if (v.dim() != w.dim()) {
        return false;
    }
    for (std::size_t i = 0, n = v.dim(); i < n; ++i) {
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
    std::size_t n = v.dim();
    assert(n == w.dim());
    Vector res(n);
    for (std::size_t i = 0; i < n; ++i) {
        res[i] = v[i] + w[i];
    }
    return res;
}

Vector operator-(const Vector& v, const Vector& w) {
    return v + (-1.0F * w);
}

Vector operator*(const Vector& v, float x) {
    return x * v;
}

Vector operator*(float x, const Vector& v) {
    int n = v.dim();
    Vector res(n);
    for (std::size_t i = 0; i < n; ++i) {
        res[i] = x * v[i];
    }
    return res;
}

Vector& operator+=(Vector& v, const Vector& w) {
    assert(v.dim() == w.dim());
    for (std::size_t i = 0, n = v.dim(); i < n; ++i) {
        v[i] += w[i];
    }
    return v;
}

Vector& operator*=(Vector& v, float x) {
    for (std::size_t i = 0, n = v.dim(); i < n; ++i) {
        v[i] *= x;
    }
    return v;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(";
    for (std::size_t i = 0; i < v.dim(); ++i) {
        os << (i > 0 ? ", " : "") << v[i];
    }
    os << ")";
    return os;
}

}  // namespace la