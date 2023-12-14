#ifndef __BIGINT_H__
#define __BIGINT_H__

#include <cstddef>
#include <iostream>

class bigint {
    char* data;
    size_t  size;
    bool    neg;

public:
    bigint();
    bigint(const bigint&);
    ~bigint();

    explicit bigint(long);
    explicit bigint(unsigned long);
    explicit bigint(const char*);

    void print() const;

    static bigint add(const bigint& left, const bigint& right);
    static bigint sub(const bigint& left, const bigint& right);
    static bigint mul(const bigint& left, const bigint& right);
    static bigint div(const bigint& left, const bigint& right);
    static bigint div(const bigint& left, const bigint& right, bigint& rest);

    // Lab-06
    static bigint gcd(const bigint& a, const bigint& b);
    static unsigned long Eratosthenes(bigint* sieve, unsigned long size);
    static bigint sqrt(const bigint& value);
};

#endif // __BIGINT_H__