#include <stdexcept>

#include "rational.h"
#include "utils.h"

/* 
 * Constructor class. By default: `num = 0`, `deno = 1`.
 * Create rational number object, or raises logical error, 
 * if denominator is zero.
 * 
 * Numerator (argument `num`) -  сan be any number.
 * Denominator (argument `deno`) - can be any number, different from zero.
 * 
 * You can create object as: `rational(n, d)`, `rational number = {n, d}`, 
 * `{n, d}`.
 * 
 * You can use this object in vector, map and set. 
 */
rational::rational (int num, int deno) {
    if (num == 0) {
        defaultRational();
    } else if (deno == 0) {
        throw std::logic_error("Error: denominator == 0!");
    } else {
        updateRational(num, deno);
    }
}
/* 
 * This function returns numerator value.
 */
int rational::numerator() const {
    return numerator_value;
}
/* 
 * This function returns denominator value.
 */
int rational::denominator() const {
    return denominator_value;
}
/* 
 * This function change numerator. Denominator don`t be changed.
 * 
 * Set default values, if numerator is zero. Otherwise update numerator.
 */
void rational::setNumerator(int num) {
    if (num == 0) {
        defaultRational();
    } else {
        updateRational(num, denominator_value);
    }
}
/* 
 * This function change denominator. Numerator don`t be changed.
 * 
 * Update denominator, if denominator not zero. 
 * Otherwise raise logical error.
 * 
 * Denominator must be value, different from zero.
 */
void rational::setDenominator(int deno) {
    if (deno != 0) {
        updateRational(numerator_value, deno);
    } else {
        throw std::logic_error("Error: denominator == 0!");
    }
}
/* 
 * This function change numerator and denominator.
 * 
 * Set default values, if numerator is zero. 
 * 
 * Update denominator, if denominator not zero. Otherwise raise logic error.
 * 
 * Denominator must value, different from zero.
 */
void rational::setRational(int num, int deno) {
    if (num == 0) {
        defaultRational();
    } else if (deno == 0) {
        throw std::logic_error("Error: denominator == 0!");
    } else {
        updateRational(num, deno);
    }    
}
/* 
 * This function set default values.
 * Default `numerator = 0`;
 * Default `denominator = 1`;
 */
void rational::defaultRational() {
    numerator_value = 0;
    denominator_value = 1;
}
/* 
 * This function update values.
 */
void rational::updateRational(int num, int deno) {
    int gcd = GreatestCommonDivisor(abs(num), abs(deno));
    if (gcd < abs(num)) {
        num = num / gcd;
        deno = deno / gcd;
    } 
    // check, if `deno > 0` then set num.
    // otherwise check, if `num > 0` then set `num * -1` else num.
    numerator_value = deno > 0 ? num : (num > 0 ? num * -1 : num);
    // check if `deno < 0` then set `deno * -1` else deno.
    denominator_value = deno < 0 ? deno * -1 : deno;
}

/* 
 * Overload `+=` operator for rational class.
 * Example: `a += b`.
 * 
 * If denominators equals, calls `setRational` function. 
 * Otherwise, set new numerator and denominator, and calls 
 * `setRational` function.
 * 
 * Example: `a += b`. `a` - this rational, `b` - right rational.
 * Formula: `n * (new_d / d) + right_n * (new_d / right_d)`, where 
 * `n` - numerator, `d` - denominator;
 * `new_d` - new denominator, which is the new value of the object;
 * `right_n` - numerator of right rational number, 
 * `right_d` - denominator of right rational numer;
 * 
 */
void rational::operator+=(const rational& right) {
    if (denominator_value == right.denominator()) {
        setRational(numerator_value + right.numerator(),
               denominator_value);
    } else {
        // get least common denominator
        int new_denominator = LeastCommonDenominator(denominator_value, 
                right.denominator());
        // 
        int new_numerator = numerator_value * (new_denominator / denominator_value) + 
                right.numerator() * (new_denominator / right.denominator());
        setRational(new_numerator, new_denominator);
    }
}

/* 
 * Overload `-=` operator for rational class.
 * Example: `a -= b`.
 * 
 * If denominators equals, calls `setRational` function. 
 * Otherwise, set new numerator and denominator, and calls 
 * `setRational` function.
 * 
 * Example: `a -= b`. `a` - this rational, `b` - right rational.
 * Formula: `n * (new_d / d) - right_n * (new_d / right_d)`, where 
 * `n` - numerator, `d` - denominator;
 * `new_d` - new denominator, which is the new value of the object;
 * `right_n` - numerator of right rational number, 
 * `right_d` - denominator of right rational numer;
 * 
 */
void rational::operator-=(const rational& right) {
    if (denominator_value == right.denominator()) {
        setRational(numerator_value - right.numerator(), 
               denominator_value);
    } else {
        int denominator = LeastCommonDenominator(denominator_value, 
                right.denominator());
        int numerator = numerator_value * (denominator / denominator_value) - 
                right.numerator() * (denominator / right.denominator());
        setRational(numerator, denominator); 
    }    
} 

/* 
 * Overload `*=` operator for rational class.
 * Example: `a *= b`.
 * 
 * Calls `setRational` function. 
 * 
 * Example: `a *= b`. `a` - this rational, `b` - right rational.
 * Left numerator multiplication on right numerator,
 * left denominator multiplication on right denominator.
 * 
 */
void rational::operator*=(const rational& right) {
    setRational(numerator_value * right.numerator(), 
            denominator_value * right.denominator());
}

/* 
 * Overload `/=` operator for rational class.
 * Example: `a /= b`.
 * 
 * Calls `setRational` function. 
 * 
 * Example: `a /= b`. `a` - this rational, `b` - right rational.
 * Left numerator multiplication on right denominator,
 * left denominator multiplication on right numerator.
 * 
 */
void rational::operator/=(const rational& right) {
    setRational(numerator_value * right.denominator(), 
            denominator_value * right.numerator());
}

/* 
 * Overload `==` operator for rational class.
 * 
 * Returns `true` or `false` depending on the comparsion result.
 */
bool operator==(const rational& left, const rational& right) {
    if (left.numerator() == right.numerator() &&
            left.denominator() == right.denominator()) {
        return true;
    } 
    int LCD = LeastCommonDenominator(left.denominator(), right.denominator());
    return (left.numerator() * (LCD / left.denominator()) == 
            right.numerator() * (LCD / right.denominator()));
}

/* 
 * Overload `!=` operator for rational class.
 * 
 * Returns `true` or `false` depending on the comparsion result.
 */
bool operator!=(const rational& left, const rational& right) {
    if (left.numerator() == right.numerator() &&
            left.denominator() == right.denominator()) {
        return false;
    } 
    int LCD = LeastCommonDenominator(left.denominator(), right.denominator());
    return !(left.numerator() * (LCD / left.denominator()) == 
            right.numerator() * (LCD / right.denominator()));
}

/* 
 * Overload `<` operator for rational class.
 * 
 * Returns `true` or `false` depending on the comparsion result.
 */
bool operator<(const rational& left, const rational& right) {
   if (left.numerator() < right.numerator() &&
            left.denominator() == right.denominator()) {
        return true;
    } 
   int denominator = LeastCommonDenominator(left.denominator(), right.denominator());
   return (left.numerator() * (denominator / left.denominator()) < 
            right.numerator() * (denominator / right.denominator()));
}

/* 
 * Overload `>` operator for rational class.
 * 
 * Returns `true` or `false` depending on the comparsion result.
 */
bool operator>(const rational& left, const rational& right) {
   if (left.numerator() > right.numerator() &&
            left.denominator() == right.denominator()) {
        return true;
    } 
   int denominator = LeastCommonDenominator(left.denominator(), right.denominator());
   return (left.numerator() * (denominator / left.denominator()) > 
            right.numerator() * (denominator / right.denominator()));
}

/* 
 * Overload `!` operator for rational class.
 * 
 * Returns `true` or `false` depending on the comparsion result.
 * Example: rational `a = {0, 1}`, `if (!a)` - return false.
 */
bool operator!(const rational& right) {
    return !(right.denominator() == 1 && right.numerator() == 0);
}

/* 
 * Overload `+` operator for rational class.
 * Example: `c = a + b`.
 * 
 * If denominators equals, calls `setRational` function. 
 * Otherwise, set new numerator and denominator, and calls 
 * `setRational` function.
 * 
 * Example: `c = a + b`. `a` - left rational, `b` - right rational.
 * Formula: `n * (new_d / d) + right_n * (new_d / right_d)`, where 
 * `n` - numerator, `d` - denominator;
 * `new_d` - new denominator, which is the new value of the object;
 * `right_n` - numerator of right rational number, 
 * `right_d` - denominator of right rational numer;
 * 
 */
rational operator+(const rational& left, const rational& right) {
    if (left.denominator() == right.denominator()) {
        return rational(left.numerator() + right.numerator(),
               left.denominator());
    }
    int denominator = LeastCommonDenominator(left.denominator(), 
            right.denominator());
    int numerator = left.numerator() * (denominator / left.denominator()) + 
            right.numerator() * (denominator / right.denominator());
    return rational(numerator, denominator);
}

/* 
 * Overload `-` operator for rational class.
 * Example: `c = a - b`.
 * 
 * If denominators equals, calls `setRational` function. 
 * Otherwise, set new numerator and denominator, and calls 
 * `setRational` function.
 * 
 * Example: `c = a - b`. `a` - left rational, `b` - right rational.
 * Formula: `n * (new_d / d) - right_n * (new_d / right_d)`, where 
 * `n` - numerator, `d` - denominator;
 * `new_d` - new denominator, which is the new value of the object;
 * `right_n` - numerator of right rational number, 
 * `right_d` - denominator of right rational numer;
 * 
 */
rational operator-(const rational& left, const rational& right) {
    if (left.denominator() == right.denominator()) {
        return rational(left.numerator() - right.numerator(), 
               left.denominator());
    } 
    int denominator = LeastCommonDenominator(left.denominator(), 
            right.denominator());
    int numerator = left.numerator() * (denominator / left.denominator()) - 
            right.numerator() * (denominator / right.denominator());
    return rational(numerator, denominator); 
} 

/* 
 * Overload `/` operator for rational class.
 * Example: `c = a / b`.
 * 
 * Calls `setRational` function. 
 * 
 * Example: `c = a / b`. `a` - left rational, `b` - right rational.
 * Left numerator multiplication on right denominator,
 * left denominator multiplication on right numerator.
 * 
 */
rational operator/(const rational& left, const rational& right) {
    return rational(left.numerator() * right.denominator(), 
            left.denominator() * right.numerator());
}

/* 
 * Overload `*` operator for rational class.
 * Example: `c = a * b`.
 * 
 * Calls `setRational` function. 
 * 
 * Example: `c = a * b`. `a` - left rational, `b` - right rational.
 * Left numerator multiplication on right numerator,
 * left denominator multiplication on right denominator.
 * 
 */
rational operator*(const rational& left, const rational& right) {
    return rational(left.numerator() * right.numerator(), 
            left.denominator() * right.denominator());
}

// set namespace std.
using namespace std;

/* 
 * Overload `>>` operator for rational class.
 * 
 * Calls `setRational` function if istream not empty.
 * 
 * Input rational must be: `n/d`, with `/` separator.
 * 
 * Returns istream.
 */
istream& operator>>(istream& stream, rational& rational) {
    int numerator, denominator;
    stream >> numerator;
    // ignore separator.
    stream.ignore(1);
    stream >> denominator;
    if (!stream.fail()) {
        rational.setRational(numerator, denominator);
    }    
    return stream;
}

/* 
 * Overload `<<` operator for rational class.
 * 
 * Calls `setRational` function if ostream not empty.
 * 
 * Output rational in the format: `n/d`.
 * 
 * Returns ostream.
 */
ostream& operator<<(ostream& stream, const rational& rational) {
    stream << rational.numerator() << "/" << rational.denominator();
    return stream;
}
