#include "inc/rational.h"
#include <cassert>
#include <cmath>

namespace {

/* sgn: extracts the sign of the input. */
inline long sgn(long x) {
    return (x < 0L ? -1L : 1L);
}

/* gcd: returns the greatest common divisor of the two positive inputs. */
long gcd(long x, long y) {
    assert(x > 0 && y > 0);
    while (y != 0) {
        long temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

}  // namespace

namespace la {

Rational::Rational(long n, long d) : _n{n}, _d{d} {
    assert(d != 0L);
    canonicalize();
}

Rational& Rational::operator+=(const Rational& r) {
    _n = (_n * r._d) + (_d * r._n);
    _d = _d * r._d;
    canonicalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& r) {
    _n = (_n * r._d) - (_d * r._n);
    _d = _d * r._d;
    canonicalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& r) {
    _n = _n * r._n;
    _d = _d * r._d;
    canonicalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& r) {
    _n = _n * r._d;
    _d = _d * r._n;
    canonicalize();
    return *this;
}

/**
 * canonicalize: updates this rational number such that 
 * the numerator and denominator are coprime and the negative
 * sign (if any) is on the numerator.
 */
void Rational::canonicalize() {
    if (_n == 0L) {
        return;
    }
    long div = gcd(std::abs(_n), std::abs(_d));
    _n = sgn(_n) * sgn(_d) * std::abs(_n) / div;
    _d = std::abs(_d) / div;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.num();
    if (r.num() != 0L && r.denom() != 1L) {
        os << "/" << r.denom();
    }
    return os;
}

}  // namespace la