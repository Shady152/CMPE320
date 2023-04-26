/*

CMPE320 Assignment 1
insultgenerator.h
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Exception class for the Number of Insults that is Out of Bounds
class NumInsultsOutOfBounds
{
public:
    NumInsultsOutOfBounds(const string &message); // NumInsultsOutOfBounds declare default constructor
    string &what();                               // returns the output message

private:
    string message; // message that output due to FileException
};                  // NumInsultsOutOfBounds

// Exception class for the state of the File to be read or written
class FileException
{
public:
    FileException(const string &message); // FileException declare default constructor
    string &what();                       // returns the output message

private:
    string message; // message that output due to FileException
};                  // FileException

// class that generates the insults
class InsultGenerator
{
public:
    void initialize();                                     // reads the insults source file and separates the insult columns into separate vectors
    string talkToMe();                                     // generates one random insults
    vector<string> generate(const int &n);                 // generates n number of random insults
    void generateAndSave(const string &str, const int &n); // generates and saves n number of random insults

private:
    vector<string> col1; // vector of 1st column of insults
    vector<string> col2; // vector of 2nd column of insults
    vector<string> col3; // vector of 3rd column of insults
    int randGen(const vector<string> &vec);
}; // InsultGenerator
