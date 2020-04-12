#ifndef LA_VECTOR_H
#define LA_VECTOR_H

#include <cassert>
#include <utility>
#include <initializer_list>
#include <iostream>
#include <iomanip>

namespace la {

/**
 * Vector: represents a one-dimensional sequence of values.
 */
template <typename T, std::size_t n>
class Vector {
public:
    Vector() = default;
    Vector(T t0) {
        for (std::size_t i = 0; i < n; ++i) {
            _ent[i] = t0;
        }
    }
    Vector(std::initializer_list<T> list) {
        assert(n == list.size());
        std::size_t i = 0;
        for (T t : list) {
            _ent[i++] = t;
        }
    }

    T& operator[](std::size_t i) {
        assert(i < n); 
        return _ent[i];
    }
    const T& operator[](std::size_t i) const {
        assert(i < n); 
        return _ent[i];
    }

    std::size_t dim() const {return n;}

private:
    T _ent[n];
};

template <typename T, std::size_t n>
bool operator==(const Vector<T, n>& v, const Vector<T, n>& w) {
    for (int i = 0; i < n; ++i) {
        if (v[i] != w[i]) {
            return false;
        }
    }
    return true;
}

template <typename T, std::size_t n>
bool operator!=(const Vector<T, n>& v, const Vector<T, n>& w) {
    return !(v == w);
}

template <typename T, std::size_t n>
std::ostream& operator<<(std::ostream& os, const Vector<T, n>& v) {
    os << "(";
    for (int i = 0; i < v.dim(); ++i) {
        os << (i > 0 ? ", " : "") << v[i];
    }
    os << ")\n";
    return os;
}

}  // namespace la

#endif