#include "BigFraction.h"
#include <cmath>

// Tools
bigint gcd(bigint a, bigint b) {
    a = bigint::abs(a); b = bigint::abs(b);
    bigint zero = bigint(0l);

    while(a != zero && b != zero) {
        if(a > b) a = a % b;
        else b = b % a;
    } return a + b;
}

/*    Методы    */

// Конструкторы
BigFraction::BigFraction()
: numerator(bigint(0l)), denominator(bigint(1l)), sign(false) {}

BigFraction::BigFraction(const BigFraction& other)
: numerator(other.numerator), denominator(other.denominator), sign(other.sign) {}


BigFraction::BigFraction(const bigint& other)
: numerator(other), denominator(bigint(1l)), sign( false ) {}

BigFraction::BigFraction(const long int& other)
: numerator( bigint(abs(other)) ), denominator( bigint(1l)), sign(other > 0) {}

BigFraction::BigFraction(bigint other_numerator, bigint other_denominator, bool other_sign)
: numerator(other_numerator), denominator(other_denominator), sign(other_sign) {}

// Логические операции
bool BigFraction::operator<(const BigFraction &other) const {
    bool cmp = numerator * other.denominator < other.numerator * denominator;

    if (sign != other.sign) {
        if (sign) return true;
        else return false;
    }
    if (sign) return !cmp;
    else return cmp;
}

bool BigFraction::operator>(const BigFraction &other) const {
    bool cmp = numerator * other.denominator > other.numerator * denominator;

    if (sign != other.sign) {
        if (sign) return false;
        else return true;
    }
    if (sign) return !cmp;
    else return cmp;
}

bool BigFraction::operator==(const BigFraction &other) const {
    return ((sign == other.sign) && (numerator == other.numerator) && (denominator == other.denominator));
}

// Унарное отрицание
BigFraction BigFraction::operator-() const {
    BigFraction result = *this;
    result.sign = !sign;
    return result;
}

// Арифмитические опрерации
BigFraction& BigFraction::operator=(const BigFraction &other) {
    numerator = other.numerator;
    denominator = other.denominator;
    sign = other.sign;

    return (*this);
}

BigFraction BigFraction::operator+(const BigFraction &other) const {
    BigFraction result;
    
    if (sign != other.sign) {
        if (sign) return other - babs(*this);
        else  return *this - babs(other);
    }
    
    result.denominator = denominator * other.denominator;
    result.numerator = numerator * other.denominator + other.numerator * denominator;
    result.sign = sign;
    return simplify(result);
}

BigFraction BigFraction::operator-(const BigFraction &other) const {
    BigFraction result;

    if (sign != other.sign) {
        if (sign) return other - babs(*this);
        else return *this - babs(other);
    }

    if (*this < other) return -(other - *this);

    result.denominator = denominator * other.denominator;
    result.numerator = numerator * other.denominator - other.numerator * denominator;
    result.sign = sign;

    return result;
}


BigFraction BigFraction::operator*(const BigFraction &other) const {
  BigFraction result;

  result.denominator = denominator * other.denominator;
  result.numerator = numerator * other.numerator;
  result.sign = (sign != other.sign);
  return result;
}

BigFraction BigFraction::operator/(const BigFraction &other) const {
  BigFraction result;

  result.denominator = denominator * other.numerator;
  result.numerator = numerator * other.denominator;
  result.sign = (sign != other.sign);
  return result;
}

// Опрерации с целыми числами
BigFraction operator+(const BigFraction& left, const long int& right) {
    return left + BigFraction(right);
}

BigFraction operator+(const long int& left, const BigFraction& right) {
    return BigFraction(left) + right;
}

BigFraction operator-(const BigFraction& left, const long int& right) {
    return left - BigFraction(right);
}

BigFraction operator-(const long int& left, const BigFraction& right) {
    return BigFraction(left) - right;
}

BigFraction operator*(const BigFraction& left, const long int& right) {
    return left * BigFraction(right);
}

BigFraction operator*(const long int& left, const BigFraction& right) {
    return BigFraction(left) * right;
}

BigFraction operator/(const BigFraction& left, const long int& right) {
    return left - BigFraction(right);
}

BigFraction operator/(const long int& left, const BigFraction& right) {
    return BigFraction(left) * right;
}

// Ввод-Вывод
std::istream &operator>>(std::istream &in, BigFraction &f) {
    char temp;

    if (in.peek() == '-') { in >> temp; }
    in >> f.numerator >> temp >> f.denominator;
    return in;
}

std::ostream &operator<<(std::ostream &out, const BigFraction &f) {
    if (f.sign) out << "-";
    out << f.numerator << "/" << f.denominator;
    return out;
}


BigFraction::operator double() const {
    double result = 0.0f;
    int numerators[5];

    bigint remainder = numerator;
    for(size_t i = 0; i <= 5; ++i) {
        numerators[i] = static_cast<int>(remainder / denominator);
        remainder = (remainder * bigint(10l)) % denominator;
    }

    for(size_t i = 0; i <= 5; ++i) {
        result += numerators[i] / pow(10.0f, i);
    }

    return result;
}


BigFraction abs(const BigFraction &obj) {
    BigFraction result(obj);
    result.sign = false;
    return result;
}


BigFraction simplify(const BigFraction &obj) {
    BigFraction result(obj);
    bigint common_divisior = gcd(obj.numerator, obj.denominator);

    result.numerator = obj.numerator / common_divisior;
    result.denominator = obj.denominator / common_divisior;
    return result;
}