#ifndef LA_RATIONAL_H
#define LA_RATIONAL_H

#include <iostream>

namespace la {

/**
 * Rational: represents a number that can be expressed as the 
 * quotient of two integers.
 */
class Rational {
public:
    Rational(long n = 0L, long d = 1L);

    Rational& operator+=(const Rational& r);
    Rational& operator-=(const Rational& r);
    Rational& operator*=(const Rational& r);
    Rational& operator/=(const Rational& r);

    explicit operator double() const {return 1.0 * _n / _d;}

    long num() const {return _n;}
    long denom() const {return _d;}

private:
    void canonicalize();

    long _n;  // numerator
    long _d;  // denominator
};

inline Rational operator+(const Rational& r1, const Rational& r2) {return Rational(r1) += r2;}
inline Rational operator+(long x, const Rational& r) {return Rational(x) + r;}
inline Rational operator+(const Rational& r, long x) {return r + Rational(x);}

inline Rational operator-(const Rational& r1, const Rational& r2) {return Rational(r1) -= r2;}
inline Rational operator-(long x, const Rational& r) {return Rational(x) - r;}
inline Rational operator-(const Rational& r, long x) {return r - Rational(x);}

inline Rational operator*(const Rational& r1, const Rational& r2) {return Rational(r1) *= r2;}
inline Rational operator*(long x, const Rational& r) {return Rational(x) * r;}
inline Rational operator*(const Rational& r, long x) {return r * Rational(x);}

inline Rational operator/(const Rational& r1, const Rational& r2) {return Rational(r1) /= r2;}
inline Rational operator/(long x, const Rational& r) {return Rational(x) / r;}
inline Rational operator/(const Rational& r, long x) {return r / Rational(x);}

inline bool operator==(const Rational& r1, const Rational& r2) {
    return r1.num() == r2.num() && (r1.num() == 0L || r1.denom() == r2.denom());
}
inline bool operator==(long x, const Rational& r) {return Rational(x) == r;}
inline bool operator==(const Rational& r, long x) {return r == Rational(x);}

inline bool operator!=(const Rational& r1, const Rational& r2) {return !(r1 == r2);}
inline bool operator!=(long x, const Rational& r) {return Rational(x) != r;}
inline bool operator!=(const Rational& r, long x) {return r != Rational(x);}

inline bool operator<(const Rational& r1, const Rational& r2) {
    return r1.num() * r2.denom() < r2.num() * r1.denom();
}
inline bool operator<(long x, const Rational& r) {return Rational(x) < r;}
inline bool operator<(const Rational& r, long x) {return r < Rational(x);}

std::ostream& operator<<(std::ostream& os, const Rational& r);

}  // namespace la

#endif