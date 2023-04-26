/*

CMPE320 Assignment 4
ShapesGood Header File
*/

#pragma once

#include <string>
using namespace std;

// --------------------------------- Shape
class Shape
{
public:
    Shape();
    Shape(const int length, const int width, const string &outlineColor);
    virtual ~Shape();
    int getLength() const;
    int getWidth() const;
    string getOutlineColor() const;
    virtual void draw() = 0;

private:
    int length;
    int width;
    string outlineColor;
};

// --------------------------------- Fillable
class Fillable
{
public:
    Fillable(const string &fillColor);
    virtual ~Fillable();
    string getFillColor() const;
    virtual void fill() = 0;

private:
    string fillColor;
};

// --------------------------------- PlaceText
class PlaceText
{
public:
    PlaceText(const string &text);
    virtual ~PlaceText();
    string getText() const;
    virtual void writeText() = 0;

private:
    string text;
};

// --------------------------------- Square
class Square : public Shape
{
public:
    Square(const int length, const int width, const string &outlineColor);
    virtual ~Square();
    virtual void draw();
};

class FilledSquare : public Fillable, public Square
{
public:
    FilledSquare(const int length, const int width, const string &outlineColor, const string &fillColor);
    virtual ~FilledSquare();
    virtual void fill();
    virtual void draw();
};

class FilledTextSquare : public PlaceText, public FilledSquare
{
public:
    FilledTextSquare(const int length, const int width, const string &outlineColor, const string &fillColor, const string &text);
    virtual ~FilledTextSquare();
    void writeText();
    virtual void draw();
};

// --------------------------------- Circle
class Circle : public Shape
{
public:
    Circle(const int length, const int width, const string &outlineColor);
    virtual ~Circle();
    virtual void draw();
};

class FilledCircle : public Fillable, public Circle
{
public:
    FilledCircle(const int length, const int width, const string &outlineColor, const string &fillColor);
    virtual ~FilledCircle();
    virtual void fill();
    virtual void draw();
};

// --------------------------------- Arc
class Arc : public Shape
{
public:
    Arc(const int length, const int width, const string &outlineColor);
    virtual ~Arc();
    virtual void draw();
};
