#ifndef __BIGINT_H__
#define __BIGINT_H__

#include <iostream>
#include <cstddef>


class bigint {
    size_t  size;
    char*   value;
    bool    is_negative;
    
public:
    bigint();
    bigint(const bigint& other);
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
};

#endif // __BIGINT_H__