#include "bigint.h"

// Utilities
int comp(char* num1, size_t lenth1, char* num2, size_t lenth2) {
    if (lenth1 > lenth2) {
        return 1; // |num1| > |num2|
    }
    else if (lenth1 < lenth2) {
        return 3; // |num1| < |num2|
    }
    else {
        for (long i = static_cast<long>(lenth1) - 1; i >= 0; ++i) {
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

// Class methods
bigint::bigint()
    : size(0), value(NULL), is_negative(false)
{}


bigint::bigint(const bigint &other)
        : size(other.size), is_negative(other.is_negative)
{
    try
    {
        value = new char[size];
    }
    catch (...)
    {
        std::cerr << "Error allocating memory" << std::endl;
    }

    for (size_t i = 0; i < other.size; ++i)
    {
        value[i] = other.value[i];
    }
}


bigint::~bigint() {
    delete[] value;
    value = NULL;
}


bigint::bigint(unsigned long num) {
    is_negative = false;
    size = 0;
    for (unsigned long n = num; n != 0; n /= 10) { ++size; }

    try {
        value = new char[size];
    }
    catch (...) {
        std::cerr << "Error allocating memory" << std::endl;
    }

    for (size_t i = 0; i < size; ++i) {
      value[i] = num % 10;
      num /= 10;
    }
}


bigint::bigint(long num) {
    is_negative = (num < 0);
    num *= (is_negative) ? (-1) : (1);

    size = 0;
    for (unsigned long n = num; n != 0; n /= 10) { ++size; }

    try {
        value = new char[size];
    }
    catch (...) {
        std::cerr << "Error allocating memory" << std::endl;
    }

    for (size_t i = 0; i < size; ++i) {
      value[i] = num % 10;
      num /= 10;
    }
}


bigint::bigint(const char *num) {
    is_negative = (num[0] == '-');
    size = 0;

    int sign = (is_negative) ? 1 : 0;

    for (size_t i = sign; num[i] != '\0'; ++i) { ++size; }

    try {
        value = new char[size];
    }
    catch (...) {
        std::cerr << "Error allocating memory" << std::endl;
        exit(-1);
    }

    for (long i = size - 1; i >= 0; --i) {
        value[i] = num[(size - 1) - i + sign] - '0';
    }
}


void bigint::print() const {
    if (is_negative) {
        std::cout << "-";
    }
    for (long i = size - 1; i >= 0; --i) {
        std::cout << static_cast<int>( value[i] );
    }
    std::cout << std::endl;
}


bigint bigint::add(const bigint &left, const bigint &right) {
    size_t cur_size = std::min(left.size, right.size) + 1;
    int *cur_value = new int[cur_size];

    bigint ans;

    for (size_t i = 0; i < cur_size; ++i) {
      cur_value[i] = 0;
    }

    size_t size_min = std::min(left.size, right.size);

    if (left.is_negative == right.is_negative) {        
        int left_digit, right_digit;

        for (size_t i = 0; i < cur_size; ++i) {
            right_digit = (i < right.size) ? (right.value[i]) : (0);
            left_digit  = (i < left.size)  ? (left.value[i])  : (0);

            cur_value[i] = left_digit + right_digit;
        }

        for (size_t i = 0; i < cur_size - 1; ++i) {
            if (cur_value[i] >= 10) {
                cur_value[i] -= 10;
                ++cur_value[i + 1];
            }
        }
        
        ans.size = cur_size;
        ans.size -= (cur_value[cur_size - 1] == 0) ? (1) : (0);

        ans.is_negative = right.is_negative;
        ans.value = new char[ans.size];

        for(size_t i = 0; i < ans.size; ++i) {
            ans.value[i] = cur_value[i];
        }

        delete[] cur_value;
    }
    else {
        
        int left_digit, right_digit;

        for (size_t i = 0; i < cur_size; ++i) {
            right_digit = (i < right.size) ? (right.value[i]) : (0);
            left_digit  = (i < left.size)  ? (left.value[i])  : (0);

            cur_value[i] = left_digit - right_digit;
        }

        bool absolute_sign = true;

        for (size_t i = 0; i < cur_size; ++i) {
            if (cur_value[cur_size - 1 - i] != 0) {
                absolute_sign = cur_value[cur_size - 1 - i] > 0;
                break;
            }
            if (i == cur_size - 1 && left.is_negative) {
                absolute_sign = false;
            }
        }

        if (absolute_sign) {
            for (size_t i = 0; i < cur_size - 1; ++i) {
                if (cur_value[i] < 0) {
                    cur_value[i] += 10;
                    --cur_value[i + 1];
                }
            }
        }
        else {
            for (size_t i = 0; i < cur_size; ++i) {
                cur_value[i] = -cur_value[i];
            }
            for (size_t i = 0; i < cur_size; ++i) {
                if (cur_value[i] < 0) {
                    cur_value[i] += 10;
                    --cur_value[i + 1];
                }
            }
        }

        size_t i = 0;

        while ((cur_value[cur_size--] == 0)  && (cur_size > 1)) {}

        ans.size = cur_size + 1;
        ans.is_negative = (absolute_sign == left.is_negative);
        ans.value = new char[ans.size];

        for(size_t i = 0; i < ans.size; ++i) {
            ans.value[i] = cur_value[i];
        }

        delete[] cur_value;
    }
    return ans;
}


bigint bigint::sub(const bigint &left, const bigint &right) {
    bigint right_copy(right);
    right_copy.is_negative = !right_copy.is_negative;
    return add(left, right_copy);
}


bigint bigint::mul(const bigint& left, const bigint& right) {
    bigint ans;

    ans.size = left.size + right.size;
    ans.value = new char[ans.size];
    ans.is_negative = left.is_negative;

    for (size_t i = 0; i < ans.size; ++i) {
        ans.value[i] = 0;
    }

    char rem;
    for (size_t i = 0; i < right.size; ++i) {
        rem = 0;
        for (size_t j = 0; j < left.size; ++j) {
            ans.value[i + j] += right.value[i] * left.value[j];
        }
    }

    for(size_t i = 0; i < ans.size; ++i) {
        if(ans.value[i] > 10) {
            ans.value[i + 1] += ans.value[i] / 10;
        }
        ans.value[i] %= 10;
    }

    ans.value = remove_lead_zeros(ans.value, ans.size);

    return ans;
}


bigint bigint::div(const bigint& left, const bigint& right) {
    bigint left_copy(left);
    bigint right_copy(right);

    left_copy.is_negative = false;
    right_copy.is_negative = false;

    bigint ans(left_copy);

    for (size_t i = 0; i < ans.size; ++i) {
        ans.value[i] = 0;
    }

    char x;
    for (long i = ans.size - 1; i >= 0; --i) {
        x = 0;
        while (!sub(left_copy, mul(right_copy, ans)).is_negative) {
            ans.value[i] = ++x;
        } ans.value[i] = --x;
    }

    ans.value = remove_lead_zeros(ans.value, ans.size);
    ans.is_negative = (left.is_negative != right.is_negative);

    return ans;
}


bigint bigint::div(const bigint& left, const bigint& right, bigint& rest) {
    bigint ans = div(left, right);
    bigint *temp = new bigint(sub(left, mul(ans, right)));

    rest.size = temp-> size;
    rest.value = temp-> value;
    rest.is_negative = temp-> is_negative;

    temp->value = NULL;

    delete temp;
    return ans;
}