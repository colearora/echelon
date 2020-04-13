#ifndef LA_VECTOR_H
#define LA_VECTOR_H

#include <iostream>
#include <utility>

namespace la {

/**
 * Vector: represents a one-dimensional sequence of floating-point values.
 */
class Vector {
public:
    Vector(std::size_t n);
    Vector(std::size_t n, float initVal);
    Vector(std::initializer_list<float> list);
    Vector(const Vector& v);
    ~Vector();

    Vector& operator=(const Vector& v);
    float& operator[](std::size_t i);
    const float& operator[](std::size_t i) const;

    std::size_t dim() const;

private:
    std::size_t _n;  // number of entries
    float* _ent;     // pointer to first entry
};

bool operator==(const Vector& v, const Vector& w);
bool operator!=(const Vector& v, const Vector& w);
Vector operator+(const Vector& v, const Vector& w);
Vector operator-(const Vector& v, const Vector& w);
Vector operator*(const Vector& v, float x);
Vector operator*(float x, const Vector& v);
Vector& operator+=(Vector& v, const Vector& w);
Vector& operator*=(Vector& v, float x);
std::ostream& operator<<(std::ostream& os, const Vector& v);

}  // namespace la

#endif