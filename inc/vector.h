#pragma once

#include "inc/util.h"
#include <initializer_list>
#include <iostream>

namespace la
{

/**
 * Vector: represents a one-dimensional sequence of floating-point values.
 */
class Vector
{
public:
    explicit Vector(int n);
    Vector(int n, float initVal);
    Vector(std::initializer_list<float> list);
    Vector(const Vector& v);
    ~Vector();

    Vector& operator=(const Vector& v);
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector& operator*=(float x);
    float& operator[](int i);
    const float& operator[](int i) const;

    float* begin();
    const float* begin() const;
    float* end();
    const float* end() const;

    int size() const;

    // Factories:
    static Vector random(int n);
    static Vector random(int n, float lo, float hi);

private:
    int _n;      // number of entries
    float* _ep;  // pointer to first entry
};

bool operator==(const Vector& v, const Vector& w);
bool operator!=(const Vector& v, const Vector& w);
Vector operator+(const Vector& v, const Vector& w);
Vector operator-(const Vector& v, const Vector& w);
Vector operator*(const Vector& v, float x);
Vector operator*(float x, const Vector& v);
std::ostream& operator<<(std::ostream& os, const Vector& v);

Vector round(const Vector& v, float epsilon = DEFAULT_EPSILON);
bool approxEqual(const Vector& v, const Vector& w,
                 float epsilon = DEFAULT_EPSILON);

Vector homogenize(const Vector& v);
Vector dehomogenize(const Vector& v);

}  // namespace la

