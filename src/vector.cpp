#include "inc/vector.h"
#include "inc/util.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace la
{

Vector::Vector(int n)
{
    assert(n > 0);
    _n = n;
    _ep = new float[n];
}

Vector::Vector(int n, float initVal)
: Vector(n)
{
    for (int i = 0; i < _n; ++i)
    {
        _ep[i] = initVal;
    }
}

Vector::Vector(std::initializer_list<float> list)
: Vector(list.size())
{
    int i = 0;
    for (float val : list)
    {
        _ep[i++] = val;
    }
}

Vector::Vector(const Vector& v)
: Vector(v._n)
{
    for (int i = 0; i < _n; ++i)
    {
        _ep[i] = v[i];
    }
}

Vector::~Vector()
{
    delete[] _ep;
}

Vector& Vector::operator=(const Vector& v)
{
    assert(_n == v._n);
    for (int i = 0; i < _n; ++i)
    {
        _ep[i] = v[i];
    }
    return *this;
}

Vector& Vector::operator+=(const Vector& v)
{
    assert(_n == v._n);
    for (int i = 0; i < _n; ++i)
    {
        _ep[i] += v[i];
    }
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    assert(_n == v._n);
    for (int i = 0; i < _n; ++i)
    {
        _ep[i] -= v[i];
    }
    return *this;
}

Vector& Vector::operator*=(float x)
{
    for (int i = 0; i < _n; ++i)
    {
        _ep[i] *= x;
    }
    return *this;
}

float& Vector::operator[](int i)
{
    assert(i >= 0 && i < _n);
    return _ep[i];
}

const float& Vector::operator[](int i) const
{
    assert(i >= 0 && i < _n);
    return _ep[i];
}

float* Vector::begin()
{
    return _ep;
}

const float* Vector::begin() const
{
    return _ep;
}

float* Vector::end()
{
    return _ep + _n;
}

const float* Vector::end() const
{
    return _ep + _n;
}

int Vector::size() const
{
    return _n;
}

Vector Vector::random(int n)
{
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
    Vector r(n);
    float denom = 1.0F / RAND_MAX;
    for (float& entry : r)
    {
        entry = std::rand() * denom;  // in [0, 1]
    }
    return r;
}

Vector Vector::random(int n, float lo, float hi)
{
    assert(hi >= lo);
    return (hi - lo) * random(n) + Vector(n, lo);
}

bool operator==(const Vector& v, const Vector& w)
{
    if (&v == &w)
    {
        return true;
    }
    if (v.size() != w.size())
    {
        return false;
    }
    for (int i = 0, n = v.size(); i < n; ++i)
    {
        if (v[i] != w[i])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const Vector& v, const Vector& w)
{
    return !(v == w);
}

Vector operator+(const Vector& v, const Vector& w)
{
    return Vector(v) += w;
}

Vector operator-(const Vector& v, const Vector& w)
{
    return Vector(v) -= w;
}

Vector operator*(const Vector& v, float x)
{
    return Vector(v) *= x;
}

Vector operator*(float x, const Vector& v)
{
    return Vector(v) *= x;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "(";
    for (int i = 0; i < v.size(); ++i)
    {
        os << (i > 0 ? ", " : "") << v[i];
    }
    os << ")";
    return os;
}

Vector round(const Vector& v, float epsilon)
{
    Vector w(v);
    for (float& entry : w)
    {
        float rounded = std::round(entry);  // to nearest integer
        if (rounded == -0.0F)
        {
            rounded = 0.0F;
        }
        if (approxEqual(entry, rounded, epsilon))
        {
            entry = rounded;
        }
    }
    return w;
}

bool approxEqual(const Vector& v, const Vector& w, float epsilon)
{
    if (&v == &w)
    {
        return true;
    }
    if (v.size() != w.size())
    {
        return false;
    }
    for (int i = 0; i < v.size(); ++i)
    {
        if (!approxEqual(v[i], w[i], epsilon))
        {
            return false;
        }
    }
    return true;
}

Vector homogenize(const Vector& v)
{
    int n = v.size();
    Vector w(n + 1);
    for (int i = 0; i < n; ++i)
    {
        w[i] = v[i];
    }
    w[n] = 1.0F;
    return w;
}

Vector dehomogenize(const Vector& v)
{
    int n = v.size();
    assert(n > 0 && v[n - 1] != 0.0F);
    Vector w(n - 1);
    for (int i = 0; i < n - 1; ++i)
    {
        w[i] = v[i] / v[n - 1];
    }
    return w;
}

}  // namespace la