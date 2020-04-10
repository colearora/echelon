#ifndef LA_VECTOR_H
#define LA_VECTOR_H

#include <cassert>
#include <utility>
#include <initializer_list>

namespace la {

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
        assert(list.size() <= n);
        std::size_t i = 0;
        for (T t : list) {
            _ent[i++] = t;
        }
        while (i < n) {
            _ent[i++] = T();
        }
    }

    T& operator[](std::size_t i) {assert(i < n); return _ent[i];}
    const T& operator[](std::size_t i) const {assert(i < n); return _ent[i];}

     std::size_t dim() const {return n;}

private:
    T _ent[n];
};

template <typename T, std::size_t m, std::size_t n>
class Matrix {
public:
    Matrix() = default;
    Matrix(T t0) {
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                _ent[j][i] = t0;
            }
        }
    }
    Matrix(std::initializer_list<std::initializer_list<T>> list) {
        // TODO
    }

    T& operator()(int i, int j) {assert(i < m && j < n); return _ent[j][i];}
    const T& operator()(int i, int j) const {assert(i < m && j < n); return _ent[j][i];}
    Vector<T, m>& operator[](int j) {
        assert(j < n);
        return *reinterpret_cast<Vector<T, m>*>(_ent[j]);
    }
    const Vector<T, m>& operator[](int j) const {
        assert(j < n);
        return *reinterpret_cast<Vector<T, m>*>(_ent[j]);
    }

    std::size_t rows() const {return m;}
    std::size_t cols() const {return n;}

private:
    T _ent[n][m];  // column major
};

}  // namespace la

#endif