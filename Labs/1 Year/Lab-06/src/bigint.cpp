#include "bigint.h"

// Utilities
int cmp(char* num1, size_t size1, char* num2, size_t size2) {
    if (size1 > size2) {
        return 1; // |num1| > |num2|
    }
    else if (size1 < size2) {
        return 3; // |num1| < |num2|
    }
    else {
        for (long i = static_cast<long>(size1) - 1; i >= 0; ++i) {
            if (num1[i] > num2[i]) {
                return 1;
            }
            else if (num1[i] < num2[i]) {
                return 3;
            }
        }
        return 2; // |num1| = |num2|
    }
}

char *remove_lead_zeros(char *source, size_t &size) {
    while (source[size - 1] == 0 && size > 1) { --size; }

    char *dest = new char[size];
    for (size_t i = 0; i < size; ++i) {
        dest[i] = source[i];
    }

    delete[] source;
    return dest;
}

// Methods
bigint::bigint()
    : size(0), data(NULL), neg(false)
{}


bigint::bigint(const bigint &other)
    : size(other.size), neg(other.neg)
{
    try {
        data = new char[size];
    }
    catch (...) {
        std::cerr << "Error allocating memory" << std::endl;
    }

    for (size_t i = 0; i < other.size; ++i)
        data[i] = other.data[i];
}


bigint::~bigint() {
    delete[] data;
    data = NULL;
}


bigint::bigint(unsigned long num) {
    neg = false;
    size = 0;
    for (unsigned long n = num; n != 0; n /= 10) { ++size; }

    try {
        data = new char[size];
    }
    catch (...) {
        std::cerr << "Error allocating memory" << std::endl;
    }

    for (size_t i = 0; i < size; ++i) {
        data[i] = num % 10;
        num /= 10;
    }
}


bigint::bigint(long num) {
    neg = (num < 0);
    num *= (neg) ? (-1) : (1);

    size = 0;
    for (unsigned long n = num; n != 0; n /= 10) { ++size; }

    try {
        data = new char[size];
    }
    catch (...) {
        std::cerr << "Error allocating memory" << std::endl;
    }

    for (size_t i = 0; i < size; ++i) {
        data[i] = num % 10;
        num /= 10;
    }
}


bigint::bigint(const char *num) {
    neg = (num[0] == '-');
    size = 0;

    int sign = (neg) ? 1 : 0;

    for (size_t i = sign; num[i] != '\0'; ++i) { ++size; }

    try {
        data = new char[size];
    }
    catch (...) {
        std::cerr << "Error allocating memory" << std::endl;
        exit(-1);
    }

    for (long i = size - 1; i >= 0; --i) {
        data[i] = num[(size - 1) - i + sign] - '0';
    }
}


void bigint::print() const {
    if (neg) {
        std::cout << "-";
    }
    for (long i = size - 1; i >= 0; --i) {
        std::cout << static_cast<int>( data[i] );
    }
    std::cout << std::endl;
}


bigint bigint::add(const bigint &left, const bigint &right) {
    size_t cur_size = std::min(left.size, right.size) + 1;
    int *cur_data = new int[cur_size];

    bigint ans;

    for (size_t i = 0; i < cur_size; ++i) {
        cur_data[i] = 0;
    }

    size_t size_min = std::min(left.size, right.size);

    if (left.neg == right.neg) {
        int left_digit, right_digit;

        for (size_t i = 0; i < cur_size; ++i) {
            right_digit = (i < right.size) ? (right.data[i]) : (0);
            left_digit  = (i < left.size)  ? (left.data[i])  : (0);

            cur_data[i] = left_digit + right_digit;
        }

        for (size_t i = 0; i < cur_size - 1; ++i) {
            if (cur_data[i] >= 10) {
                cur_data[i] -= 10;
                ++cur_data[i + 1];
            }
        }

        ans.size = cur_size;
        ans.size -= (cur_data[cur_size - 1] == 0) ? (1) : (0);

        ans.neg = right.neg;
        ans.data = new char[ans.size];

        for(size_t i = 0; i < ans.size; ++i) {
            ans.data[i] = cur_data[i];
        }

        delete[] cur_data;
    }
    else {
        if(left.neg && right.neg) {
            bigint right_copy(right);
            bigint left_copy(left);
            right_copy.neg = false;
            left_copy.neg = false;
            return sub(right_copy, left_copy);
        }
        else if(left.neg && !right.neg) {
            bigint right_copy(right);
            right_copy.neg = true;
            return add(left, right_copy);
        }

        int flag = cmp(left.data, left.size, right.data, right.size);
        if(flag == 2) { // left == right
            return bigint(0l);
        }
        else if (flag == 3) { // left < right |-> Negative number
            bigint right_copy(right);
            bigint left_copy(left);
            right_copy.neg = false;
            left_copy.neg = false;
            bigint ans = sub(right_copy, left_copy);
            ans.neg = true;
            return ans;
        }

        int left_digit, right_digit;

        for (size_t i = 0; i < cur_size; ++i) {
            right_digit = (i < right.size) ? (right.data[i]) : (0);
            left_digit  = (i < left.size)  ? (left.data[i])  : (0);

            cur_data[i] = left_digit - right_digit;
        }

        bool absolute_sign = true;

        for (size_t i = 0; i < cur_size; ++i) {
            if (cur_data[cur_size - 1 - i] != 0) {
                absolute_sign = cur_data[cur_size - 1 - i] > 0;
                break;
            }
            if (i == cur_size - 1 && left.neg) {
                absolute_sign = false;
            }
        }

        if (absolute_sign) {
            for (size_t i = 0; i < cur_size - 1; ++i) {
                if (cur_data[i] < 0) {
                    cur_data[i] += 10;
                    --cur_data[i + 1];
                }
            }
        }
        else {
            for (size_t i = 0; i < cur_size; ++i) {
                cur_data[i] = -cur_data[i];
            }
            for (size_t i = 0; i < cur_size; ++i) {
                if (cur_data[i] < 0) {
                    cur_data[i] += 10;
                    --cur_data[i + 1];
                }
            }
        }

        while ((cur_data[cur_size--] == 0)  && (cur_size > 1)) {}

        ans.size = cur_size + 1;
        ans.neg = (absolute_sign == left.neg);
        ans.data = new char[ans.size];

        for(size_t i = 0; i < ans.size; ++i) {
            ans.data[i] = cur_data[i];
        }

        delete[] cur_data;
    }
    return ans;
}


bigint bigint::sub(const bigint &left, const bigint &right) {
    bigint right_copy(right);
    right_copy.neg = !right_copy.neg;
    return add(left, right_copy);
}


bigint bigint::mul(const bigint& left, const bigint& right) {
    bigint ans;

    size_t cur_size = left.size + right.size;
    char *cur_data = new char[ans.size];

    for (size_t i = 0; i < cur_size; ++i) {
        cur_data[i] = 0;
    }

    for (size_t i = 0; i < right.size; ++i) {
        for (size_t j = 0; j < left.size; ++j) {
            cur_data[i + j] += right.data[i] * left.data[j];
        }
    }

    for(size_t i = 0; i < cur_size; ++i) {
        if(cur_data[i] > 10) {
            cur_data[i + 1] += cur_data[i] / 10;
        }
        cur_data[i] %= 10;
    }

    while ((cur_data[cur_size - 1] == 0)  && (cur_size > 1 )) { --cur_size; }

    ans.size = cur_size;
    ans.neg = left.neg;
    ans.data = new char[ans.size];

    for(size_t i = 0; i < ans.size; ++i) {
        ans.data[i] = cur_data[i];
    }

    delete[] cur_data;
    return ans;
}


bigint bigint::div(const bigint& left, const bigint& right) {
    bigint left_copy(left);
    bigint right_copy(right);

    left_copy.neg = false;
    right_copy.neg = false;

    bigint ans(left_copy);

    for (size_t i = 0; i < ans.size; ++i) {
        ans.data[i] = 0;
    }

    char x;
    for (long i = ans.size - 1; i >= 0; --i) {
        x = 0;
        while (!sub(left_copy, mul(right_copy, ans)).neg) {
            ans.data[i] = ++x;
        } ans.data[i] = --x;
    }

    size_t cur_size = ans.size;
    char *cur_data = ans.data;

    long i = cur_size - 1;
    while ((cur_data[i] == 0)  && (i != 0)) { --i; }

    ans.size = i + 1;
    ans.neg = (left.neg != right.neg);
    ans.data = new char[ans.size];

    for(size_t i = 0; i < ans.size; ++i) {
        ans.data[i] = cur_data[i];
    }

    delete[] cur_data;
    return ans;
}


bigint bigint::div(const bigint& left, const bigint& right, bigint& rest) {
    bigint ans( div(left, right) );
    bigint *temp = new bigint(sub(left, mul(ans, right)));

    rest.size = temp->size;
    rest.data = temp->data;
    rest.neg = temp->neg;

    temp->data = NULL;

    delete temp;
    return ans;
}


bigint bigint::gcd(const bigint& a, const bigint& b) {
    bigint a_copy(a);
    bigint b_copy(b);
    int flag;
    
    while (!((a_copy.size == 1) && (a_copy.data[0] == 0)) && !((b_copy.size == 1) && (b_copy.data[0] == 0))) // ( a!= 0 && b != 0 )
    {
        flag = cmp(a_copy.data, a_copy.size, b_copy.data, b_copy.size);
        if (flag == 1) { // a_
            bigint::div(bigint(a_copy), bigint(b_copy), a_copy);
            a_copy.data = remove_lead_zeros(a_copy.data, a_copy.size);
        }
        else {
            bigint::div(bigint(b_copy), bigint(a_copy), b_copy);
            b_copy.data = remove_lead_zeros(b_copy.data, b_copy.size);
        }
    }

    return add(a_copy, b_copy);
}


unsigned long bigint::Eratosthenes(bigint* sieve, unsigned long size) {
    unsigned long counter = 0;

    sieve = new bigint[size + 1];
    bool *IsPrime = new bool[size + 1];

    for(size_t i = 0; i <= size; ++i) {
        IsPrime[i] = true;
    }

    IsPrime[0] = false; IsPrime[1] = false;
    for (size_t i = 2; i <= size; ++i) {
        if (IsPrime[i]) {
            ++counter;
            for (size_t j = 2 * i; j <= size; j += i) {
                IsPrime[j] = false;
                sieve[j].size = 1;
                sieve[j].data = new char[1];
                sieve[j].data[0] = 0;
            }
        }
    }

    return counter;
}


bigint avg(const bigint& l, const bigint& r) {
    return bigint::div(bigint::add(l, r), bigint(2l));
}


bigint bigint::sqrt(const bigint& value) {
    bigint* l = new bigint(0l);
    bigint* r = new bigint( add(value, bigint(1l)) );
    bigint* m = new bigint(avg(*l, *r));

    while (cmp(l->data, l->size, m->data, m->size) != 2) {
        bigint temp = sub(mul(*m, *m), value);
        temp.data = remove_lead_zeros(temp.data, temp.size);

        if(temp.data[0] == 0 && temp.size == 1) { return *m; }
        else if (temp.neg)  { delete l; l = m; }
        else { delete r; r = m; }

        m = new bigint(avg(*l, *r));
    }

    delete l;
    delete r;

    return *m;
}
