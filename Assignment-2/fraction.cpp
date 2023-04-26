
/*

CMPE320 Assignment 2
*/

#include <iostream>
#include "fraction.h"
using namespace std;

// Fraction Exception
FractionException::FractionException(const string &message) : message(message) {}
string &FractionException::what() { return message; }

// constructor for no input
Fraction::Fraction() : numer(0), denom(1){};

// constructor for numerator and denominator input
Fraction::Fraction(int numer, int denom) : numer(numer), denom(denom)
{
    if (denom == 0)
        throw FractionException("ERROR: THE DENOMINATOR MUST BE GREATER THAN ZERO!");
    normalize(); // assures that the Fraction object is normalized and that the sign convention is correct
};

// constructor for only numerator input
Fraction::Fraction(int numer) : numer(numer), denom(1){};

// returns the numerator of the fraction object
int Fraction::numerator() const
{
    return numer;
} // numerator()

// returns the denominator of the fraction object
int Fraction::denominator() const
{
    return denom;
} // denominator()

// normalizes the fraction and fixes the sign according to the instructed convention
void Fraction::normalize()
{
    int common = gcd(abs(numer), abs(denom)); // the abs() is necessary otherwise it recurses forever
    numer /= common;
    denom /= common;
    if (numer * denom < 0)
    {
        numer = -abs(numer);
        denom = abs(denom);
    }
    else
    {
        numer = abs(numer);
        denom = abs(denom);
    }
    return;
} // normalize()

// Greatest Common Divisor Algorithm
int Fraction::gcd(const int &num, const int &denom)
{
    if ((denom <= num) && (num % denom == 0))
        return denom;
    else if (num < denom)
        return gcd(denom, num);
    else
        return gcd(denom, num % denom);
} // gcd()

// Unary operator overloads start ---------------------------------------------//

// Overload of the Pre-increment operator; taken from prof
Fraction &Fraction::operator++()
{
    numer += denom;
    return *this;
} // operator++(); Pre-increment

// Overload of the Post-increment operator; taken from prof
Fraction Fraction::operator++(int)
{
    Fraction clone(numer, denom);
    numer += denom;
    return clone;
} // operator++(); Post-increment

// negation operator overload
Fraction Fraction::operator-()
{
    numer *= -1;
    return *this;
    // return Fraction(-numer, denom);
} // operator-(); negation

// Unary operator overloads end -----------------------------------------------//

// Arithmetic operators overloads start ---------------------------------------//

// addition operator overload
Fraction operator+(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.numerator() * rhs.denominator() + rhs.numerator() * lhs.denominator(), lhs.denominator() * rhs.denominator());
} // operator+(); addition

// subtraction operator overload
Fraction operator-(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.numerator() * rhs.denominator() - rhs.numerator() * lhs.denominator(), lhs.denominator() * rhs.denominator());
} // operator-(); subtraction

// multiplication operator overload
Fraction operator*(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
} // operator*(); multiplication

// division operator overload
Fraction operator/(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.numerator() * rhs.denominator(), lhs.denominator() * rhs.numerator());
} // operator/(); division

// sum equals operator overload
Fraction Fraction::operator+=(const Fraction &addfrac)
{
    numer = numer * addfrac.denominator() + addfrac.numerator() * denom;
    denom = denom * addfrac.denominator();
    normalize();
    return *this;
} // operator+=()

// Arithmetic operators overloads end -----------------------------------------//

// Boolean operators overloads start ------------------------------------------//

// gets the difference between two fractions
int Fraction::differenceFrac(const Fraction &compfrac) const
{
    return (numer * compfrac.denominator() - denom * compfrac.numerator());
} // differenceFrac()

// checks if the left hand fraction is less than the right hand fraction
bool operator<(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.differenceFrac(rhs) < 0;
} // operator<()

// checks if the left hand fraction is less than or equal to the right hand fraction
bool operator<=(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.differenceFrac(rhs) <= 0;
} // operator<=()

// checks if the left hand fraction is equal to the right hand fraction
bool operator==(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.differenceFrac(rhs) == 0;
} // operator==()

// checks if the left hand fraction is not equal to the right hand fraction
bool operator!=(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.differenceFrac(rhs) != 0;
} // operator!=()

// checks if the left hand fraction is greater than or equal to the right hand fraction
bool operator>=(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.differenceFrac(rhs) >= 0;
} // operator>=()

// checks if the left hand fraction is greater than the right hand fraction
bool operator>(const Fraction &lhs, const Fraction &rhs)
{
    return lhs.differenceFrac(rhs) > 0;
} // operator>()

// Boolean operators overloads end --------------------------------------------//

// Stream operators overloads start -------------------------------------------//

// Insertion operator overload
ostream &operator<<(ostream &out, const Fraction &frac)
{
    out << frac.numerator() << "/" << frac.denominator();
    return out;
} // operator<<()

// extraction operator overload
istream &operator>>(istream &in, Fraction &infrac)
{
    int num, den;
    in >> num;
    if (in.peek() != 10)
    {
        char mid;
        in >> mid;
        if (mid == '/')
            in >> den;
        else
            den = 1;
        infrac = Fraction(num, den);
    }
    else
        infrac = Fraction(num);
    return in;
} // operator>>()

// Stream operators overloads end ---------------------------------------------//