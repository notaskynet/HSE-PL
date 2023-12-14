#ifndef __FRACTIONS_H__
#define __FRACTIONS_H__

#include <iostream>
#include <string>

typedef unsigned long ul;


class fraction {
public:
    fraction();
    fraction(int);
    fraction(const fraction&);

    fraction& operator=(const fraction&);
    fraction& operator=(int&);

    fraction operator+(const fraction&) const;
    fraction operator-(const fraction&) const;
    fraction operator*(const fraction&) const;
    fraction operator/(const fraction&) const;
    operator double();

    friend fraction operator+(const fraction&, const int);
    friend fraction operator+(const int, const fraction&);

    friend fraction operator-(const fraction&, const int);
    friend fraction operator-(const int, const fraction&);

    friend fraction operator*(const fraction&, const int);
    friend fraction operator*(const int, const fraction&);

    friend fraction operator/(const fraction&, const int);
    friend fraction operator/(const int, const fraction&);

    friend std::ostream& operator<<(std::ostream&, const fraction&);
    friend std::istream& operator>>(std::istream&, fraction&);

    friend fraction simplify(fraction&);

private:
    ul   numerator;
    ul   denominator;
    bool sign;
};

#endif // __FRACTIONS_H__