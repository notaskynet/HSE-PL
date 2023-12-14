#ifndef __BIGFRACTION_H__
#define __BIGFRACTION_H__

#include <iostream>

#include "fraction.h"
#include "bigint.h"


class BigFraction: public fraction {
    bigint numerator;
    bigint denominator;
    bool sign = false;

public:
    BigFraction();
    BigFraction(const BigFraction&);

    explicit BigFraction(const bigint&);
    explicit BigFraction(const long int&);
    explicit BigFraction(bigint, bigint, bool);
    
    bool operator<(const BigFraction &other) const;
    bool operator>(const BigFraction &other) const;
    bool operator==(const BigFraction &other) const;
    
    operator double() const;
    BigFraction  operator-() const;
    BigFraction& operator=(const BigFraction&);
    BigFraction  operator+(const BigFraction&) const;
    BigFraction  operator-(const BigFraction&) const;
    BigFraction  operator*(const BigFraction&) const;
    BigFraction  operator/(const BigFraction&) const;

    friend BigFraction operator+(const BigFraction&, int&);
    friend BigFraction operator+(int&, const BigFraction&);
    friend BigFraction operator-(const BigFraction&, int&);
    friend BigFraction operator-(int&, const BigFraction&);
    friend BigFraction operator*(const BigFraction&, int&);
    friend BigFraction operator*(int&, const BigFraction&);
    friend BigFraction operator/(const BigFraction&, int&);
    friend BigFraction operator/(int&, const BigFraction&);

    friend std::istream &operator>>(std::istream &in, BigFraction &f);
    friend std::ostream &operator<<(std::ostream &out, const BigFraction &f);
    
    friend BigFraction abs(const BigFraction&);
    friend BigFraction simplify(const BigFraction &);
};

#endif // __BIGFRACTION_H__