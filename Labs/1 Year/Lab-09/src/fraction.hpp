#include <iostream>
#include <cmath>

template<typename T>
class Fraction {
    T num;
    T den;
    bool sign;

    static Fraction<T> change_sign(Fraction<T> other) {
        Fraction<T> result(other);
        result.sign = !result.sign;
        return result;
    }

public:
    //Реализуем конструкторов
    Fraction<T>()
    : num( static_cast<T>(0) ), den( static_cast<T>(1) ), sign(false) {}

    Fraction<T>(const Fraction& other)
    : num(other.num), den(other.den), sign(other.sign) {}

    Fraction<T>(const T& other)
    : num( abs(other) ), den(static_cast<T>(1)), sign( other < 0 ) {}


    // Реализуем операции с дробями
    Fraction<T>& operator = (Fraction<T> other) {
        num  = other.num;
        den  = other.den;
        sign = other.sign;
        return *this;
    }

    /* Сложение */
    Fraction<T> operator + (const Fraction<T>& other) const {
        Fraction<T> result;

        if(other.sign == sign) {
            result.num  = num * other.den + other.num * den;
            result.den  = den * other.den;
            result.sign = sign;
            return result;
        }
        else return (*this) - change_sign(other);
    }

    template<typename P>
    friend Fraction<T> operator + (const Fraction<T> frac, const P num) {
        Fraction<T> frac_copy( static_cast<T>(num) );
        return frac + frac_copy;
    }

    template<typename P>
    friend Fraction<T> operator + (const P num, const Fraction<T> frac) {
        Fraction<T> frac_copy( static_cast<T>(num) );
        return frac_copy + frac;
    }

    /* Вычитание */
    Fraction operator - (const Fraction& other) const {
        if(sign != other.sign) return (*this) + change_sign(other);
        else {
            Fraction<T> result;
            
            if(num * other.den > den * other.num) {
                result.num = num * other.den - other.num * den;
                result.den = den * other.den;
                result.sign = sign;
            }
            else {
                result.num = other.num * den - num * other.den;
                result.den = den * other.den;
                result.sign = (!other.sign) && (result.num != 0);
            }
            return result;
        }
    }

    template<typename P>
    friend Fraction<T> operator - (const Fraction<T> frac, const P num) {
        Fraction<T> frac_copy( static_cast<T>(num) );
        return frac - frac_copy;
    }

    template<typename P>
    friend Fraction<T> operator - (const P num, const Fraction<T> frac) {
        Fraction<T> frac_copy( static_cast<T>(num) );
        return frac_copy - frac;
    }

    /* Умножение */
    Fraction operator * (const Fraction& other) const {
        Fraction<T> result;

        result.num  = num * other.num;
        result.den  = den * other.den;
        result.sign = (sign != other.sign);
        return result;
    }

    template<typename P>
    friend Fraction<T> operator * (const Fraction<T> frac, const P num) {
        Fraction<T> frac_copy( static_cast<T>(num) );
        return frac * frac_copy;
    }

    template<typename P>
    friend Fraction<T> operator * (const P num, const Fraction<T> frac) {
        Fraction<T> frac_copy( static_cast<T>(num) );
        return frac_copy * frac;
    }

    /* Деление */
    Fraction operator / (const Fraction& other) const {
        Fraction<T> result;

        if( other.num == static_cast<T>(0) )
            throw std::invalid_argument("Dividing by zero if forbidden");
        result.num  = num * other.den;
        result.den  = den * other.num;
        result.sign = (sign != other.sign);
        return result;

    }

    template<typename P>
    friend Fraction<T> operator / (const Fraction<T> frac, const P num) {
        Fraction<T> frac_copy( static_cast<T>(num) );
        return frac / frac_copy;
    }

    template<typename P>
    friend Fraction<T> operator / (const P num, const Fraction<T> frac) {
        Fraction<T> frac_copy( static_cast<T>(num) );
        return frac_copy / frac;
    }

    // Реализация ввода/вывода
    friend std::istream& operator >> (std::istream& in, Fraction& frac) {
        in >> frac.num;
        in.ignore(1, '/');
        in >> frac.den;
        if(frac.num < static_cast<T>(0)) {
            frac.num = -1 * frac.num;
            frac.sign = true;
        }
        if(frac.den == static_cast<T>(0))
            throw std::invalid_argument("Zero cannot be in the denominator");
        return in;
    }

    friend std::ostream& operator << (std::ostream& out, Fraction frac)  {
        if ((frac.sign) && (frac.num != static_cast<T>(0))) out << "-";
        out << frac.num << "/" << frac.den;
        return out;
    }
};
