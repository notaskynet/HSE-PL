#include "fraction.h"


// Utilities
ul gcd(ul a, ul b) {
    while(!(a + 1 == 1 || b + 1 == 1)) {
        if(a > b) a %= b;
        else b %= a;
    }
    return (a + b);
}


// Class methods
fraction::fraction()
    : numerator(0), denominator(0), sign(false)
{}


fraction::fraction(const fraction& other)
    : numerator{other.numerator}, denominator{other.denominator}, sign{other.sign}
{}


fraction::fraction(int other)
    : numerator(std::abs(other)), denominator(1), sign(other < 0)
{}


fraction& fraction::operator=(const fraction &other) {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
    this->sign = other.sign;

    return *this;
}


fraction& fraction::operator=(int &other) {
    numerator = std::abs(other);
    denominator = 1;
    sign = (other < 0);
    return *this;
}


fraction fraction::operator+(const fraction &other) const {
    fraction result;

    if(sign != other.sign) {
        fraction t(*this);
        t.sign = !t.sign;
        if(sign) return other - t; // (-a) + b = b - (-1) * (a);
        else return t - other;
    }

    result.sign = other.sign;
    result.denominator = denominator * other.denominator;
    result.numerator = numerator * other.denominator + this->denominator * other.numerator;

    return simplify(result);
}


fraction fraction::operator-(const fraction &other) const {
    fraction result;
    if(other.sign != sign) {
        fraction t(*this);
        fraction o(other);
        if(other.sign && !sign) o.sign = !o.sign;
        else t.sign != t.sign;

        return t + o;
    }
    
    if((numerator * other.denominator) < (denominator * other.numerator)) { result.sign = true; }
    else { result.sign = false; }

    result.denominator = denominator * other.denominator;
    if(numerator * other.denominator > other.numerator * denominator) {
        result.numerator = numerator * other.denominator - other.numerator * denominator;
    } else result.numerator = other.numerator * denominator - numerator * other.denominator;

    return simplify(result);
}


fraction fraction::operator*(const fraction &other) const {
    fraction result;

    result.sign = (sign, other.sign);
    result.numerator = numerator * other.numerator;
    result.denominator = denominator * other.denominator;

    return simplify(result);
}


fraction fraction::operator/(const fraction& other) const {
    fraction result;
    
    try {
        if(other.numerator == 0) { throw std::invalid_argument("Fuck C++"); }

        result.sign = (sign, other.sign);
        result.numerator = numerator * other.denominator;
        result.denominator = denominator * other.numerator;
    }
    catch(const std::invalid_argument &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return simplify(result);
}


fraction::operator double() {
    double neg = (sign) ? (-1) : (1);
    return (neg * numerator / denominator);
}


fraction operator+(const fraction& right, const int left) { return right + fraction(left); }
fraction operator+(const int right, const fraction& left) { return fraction(left) + right; }

fraction operator-(const fraction& right, const int left) { return right - fraction(left); }
fraction operator-(const int right, const fraction& left) { return fraction(left) - right; }

fraction operator*(const fraction& right, const int left) { return right * fraction(left); }
fraction operator*(const int right, const fraction& left) { return fraction(left) * right; }

fraction operator/(const fraction& right, const int left) { return right / fraction(left); }
fraction operator/(const int right, const fraction& left) { return fraction(left) / right; }


std::ostream& operator<<(std::ostream& out, const fraction& obj) {
    if (obj.numerator == 0){
        out << 0;
    }
    else {
        if(obj.sign) out << "-";
        if(obj.denominator == 1) out << obj.numerator;
        else  out << obj.numerator << "/" << obj.denominator;
    }
    return out;
}


std::istream& operator>>(std::istream& in, fraction& obj) {
    try{
        std::string s;
        obj = 0;

        in >> s;
        if(s[0] == '-') { obj.sign = true; }
        
        size_t i = (obj.sign) ? 1 : 0;
        for(; s[i] != '/'; ++i) {
            if(s[i] < '0' && s[i] > '9') throw std::invalid_argument("Wrong argument!");
            obj.numerator += (obj.numerator * 10) + static_cast<ul>(s[i] - '0');
        } ++i;
        for(; i < s.size(); ++i) {
            if(s[i] < '0' && s[i] > '9') throw std::invalid_argument("Wrong argument!");
            obj.denominator += (obj.denominator * 10) + static_cast<ul>(s[i] - '0');
        }
    }
    catch(const std::invalid_argument &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return in;
}


fraction simplify(fraction& obj) {
    ul div = gcd(obj.numerator, obj.denominator);
    obj.numerator /= div;
    obj.denominator /= div;

    return obj;
}