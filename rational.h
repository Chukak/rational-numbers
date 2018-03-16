#ifndef RATIONAL_H
#define RATIONAL_H

#include <istream>
#include <ostream>

/* 
 * Class rational.
 * 
 * Public: 
 * 1. `rational(num, deno)` - class initializer. By default `num = 0`, `deno = 1`.
 * 2. `numerator()` - return numerator value.
 * 3. `denominator()` - return denominator value.
 * 4. `setRational(num, deno)` - set new numerator and denominator values.
 * 5. `setNumerator(num)` - set new numerator value.
 * 6. `setDenominator(deno)` - set new denominator value.
 * 
 * Also operators: `+=`, `-=`, `*=`, `/=` .
 * 
 * Private:
 * 1. `numerator_value` - numerator value.
 * 2. `denominator_value` - denominator value.
 * 3. `updateRational` - update numerator and denominator values.
 * 4. `defaultRational` - set default numerator and denominator values. By 
 * default numerator = 0, denominator = 1.
 * 
 */
class rational {
public:
    rational (int num = 0, int deno = 1);
    int numerator() const;
    int denominator() const;
    void setRational(int num, int deno);
    void setNumerator(int num);
    void setDenominator(int deno);
    
    void operator+=(const rational& right);
    void operator-=(const rational& right);
    void operator*=(const rational& right);
    void operator/=(const rational& right);
    
    explicit operator bool() const {
        return (numerator_value != 0 && denominator_value != 1);
    };
    
private:
    int numerator_value;
    int denominator_value;
    
    void updateRational(int num, int deno);
    void defaultRational();
};

/* 
 * Operators:
 * `==` - check if two rational objects are equal.
 * `!=` - check if two rational objects are not equal.
 * `!` - check if not rational object, (for example, `!rational(0, 1)` - `false`).
 */
bool operator==(const rational& left, const rational& right);
bool operator!=(const rational& left, const rational& right);
bool operator!(const rational& right);

/* 
 * Operators:
 * `+` - addition two rational objects.
 * `-` - subtraction two rational objects.
 * `*` - multiplication two rational objects.
 * `/` - division two rational objects.
 */
rational operator+(const rational& left, const rational& right);
rational operator-(const rational& left, const rational& right);
rational operator/(const rational& left, const rational& right);
rational operator*(const rational& left, const rational& right);

/* 
 * Operators:
 * `<` - check, if left rational less than right rational.
 * `>` - check, if left rational more than right rational.
 */
bool operator<(const rational& left, const rational& right);
bool operator>(const rational& left, const rational& right);

/* 
 * Input/Output operators:
 * `>>` - set rational object from input.
 * `<<` - output rational object in the format `n/d`.
 */
std::istream& operator>>(std::istream& stream, rational& rational);
std::ostream& operator<<(std::ostream& stream, const rational& rational);

#endif /* RATIONAL_H */
