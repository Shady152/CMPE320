
/*

CMPE320 Assignment 2
*/

#include <iostream>
using namespace std;

class FractionException
{
public:
    FractionException(const string &message); // FractionException declare default constructor
    string &what();                           // returns the output message
private:
    string message; // message that output due to FractionException
};

class Fraction
{
public:
    Fraction();                     // no input constructor
    Fraction(int numer, int denom); // numerator and denominator constructor
    Fraction(int numer);            // only numerator input constructor
    int numerator() const;          // numerator accessor
    int denominator() const;        // denominator accessor

    Fraction &operator++();                             // pre-increment
    Fraction operator++(int);                           // post-increment
    Fraction operator-();                               // negation
    Fraction operator+=(const Fraction &frac);          // sum equals
    int differenceFrac(const Fraction &compfrac) const; // get the difference between two fractions

private:
    int numer;                                   // numerator of fraction object
    int denom;                                   // denominator of fraction object
    int gcd(const int &numer, const int &denom); // Greatest Common Divisor method
    void normalize();                            // faction normalization and sign correction method
};

// Overloaded arithmetic operators
Fraction operator+(const Fraction &lhs, const Fraction &rhs); // addition
Fraction operator-(const Fraction &lhs, const Fraction &rhs); // subtraction
Fraction operator*(const Fraction &lhs, const Fraction &rhs); // multiplication
Fraction operator/(const Fraction &lhs, const Fraction &rhs); // division

// Overloaded boolean operators
bool operator<(const Fraction &lhs, const Fraction &rhs);  // less than
bool operator<=(const Fraction &lhs, const Fraction &rhs); // less than or equal
bool operator==(const Fraction &lhs, const Fraction &rhs); // equals
bool operator!=(const Fraction &lhs, const Fraction &rhs); // not equals
bool operator>=(const Fraction &lhs, const Fraction &rhs); // greater than or equals
bool operator>(const Fraction &lhs, const Fraction &rhs);  // greater than

// Stream operators
ostream &operator<<(ostream &out, const Fraction &value); // insertion operator
istream &operator>>(istream &in, Fraction &retFrac);      // extraction operator