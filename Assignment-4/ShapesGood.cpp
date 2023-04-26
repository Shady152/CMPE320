/*

CMPE320 Assignment 4
ShapesGood Implementation File
*/

#include <iostream>
#include <string>
#include "ShapesGood.h"

using namespace std;

// ------------------------------------------------------------------- Shape Class
// Empty Shape Constructor
Shape::Shape() : length(0), width(0), outlineColor("black") {}

// Shape Constructor
Shape::Shape(int len, int w, const string &outlineColor) : length(len), width(w), outlineColor(outlineColor) {}

// Shape Destroctor
Shape::~Shape()
{
    // cout << "\nThe shape has been deleted" << endl;
}
// -------------------------------------------------------------------

// ------------------------------------------------------------------- Fillable Class
Fillable::Fillable(const string &fillColor) : fillColor(fillColor) {}

Fillable::~Fillable() {}
// -------------------------------------------------------------------

// ------------------------------------------------------------------- PlaceText Class
PlaceText::PlaceText(const string &text) : text(text) {}

PlaceText::~PlaceText() {}
// -------------------------------------------------------------------

// ------------------------------------------------------------------- Accessors
int Shape::getLength() const
{
    return length;
}
int Shape::getWidth() const
{
    return width;
}

string Shape::getOutlineColor() const
{
    return outlineColor;
}

string Fillable::getFillColor() const
{
    return fillColor;
}

string PlaceText::getText() const
{
    return text;
}
// -------------------------------------------------------------------

// ------------------------------------------------------------------- Square Class | Extends Shape Class

Square::Square(const int length, const int width, const string &outlineColor) : Shape(length, width, outlineColor) {}

Square::~Square() {}

void Square::draw()
{
    cout << "\nDrawing a " + getOutlineColor() + " square.";
}

// -------------------------------------------------------------------

// ------------------------------------------------------------------- FilledSquare | Extends Square and Fillable Classes

FilledSquare::FilledSquare(const int length, const int width, const string &outlineColor, const string &fillColor) : Square(length, width, outlineColor), Fillable(fillColor) {}

FilledSquare::~FilledSquare() {}

void FilledSquare::fill()
{
    cout << " With " + getFillColor() + " fill.";
}

void FilledSquare::draw()
{
    Square::draw();
    FilledSquare::fill();
}
// -------------------------------------------------------------------

// ------------------------------------------------------------------- FilledTextSquare | Extends PlaceText and FilledSquare

FilledTextSquare::FilledTextSquare(const int length, const int width, const string &outlineColor, const string &fillColor, const string &text) : FilledSquare(length, width, outlineColor, fillColor), PlaceText(text) {}

FilledTextSquare::~FilledTextSquare() {}

void FilledTextSquare::writeText()
{
    cout << " Containing the text: \"" << getText() << "\".";
}

void FilledTextSquare::draw()
{
    Square::draw();
    FilledSquare::fill();
    FilledTextSquare::writeText();
}
// ------------------------------------------------------------------- Circle Class | Extends Shape Class
Circle::Circle(const int length, const int width, const string &outlineColor) : Shape(length, width, outlineColor) {}

Circle::~Circle() {}

void Circle::draw()
{
    cout << "\nDrawing a " + getOutlineColor() + " circle.";
}

// -------------------------------------------------------------------

// ------------------------------------------------------------------- FilledCircle Class | Extends Circle and Fillable Classes
FilledCircle::FilledCircle(const int length, const int width, const string &outlineColor, const string &fillColor) : Circle(length, width, outlineColor), Fillable(fillColor) {}

FilledCircle::~FilledCircle() {}

void FilledCircle::fill()
{
    cout << " With " + getFillColor() + " fill.";
}

void FilledCircle::draw()
{
    Circle::draw();
    FilledCircle::fill();
}
// -------------------------------------------------------------------

// ------------------------------------------------------------------- Arc Class | Extends Shape Class
Arc::Arc(const int length, const int width, const string &outlineColor) : Shape(length, width, outlineColor) {}

Arc::~Arc() {}

void Arc::draw()
{
    cout << "\nDrawing a " + getOutlineColor() + " arc.";
}
// -------------------------------------------------------------------
