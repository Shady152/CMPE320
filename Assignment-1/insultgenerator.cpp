/*

CMPE320 Assignment 1
insultgenerator.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <time.h>
#include "insultgenerator.h"
using namespace std;

// taken from the profs example
FileException::FileException(const string &message) : message(message) {}
string &FileException::what() { return message; }

// taken from the profs example
NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string &message) : message(message) {}
string &NumInsultsOutOfBounds::what() { return message; }

void InsultGenerator::initialize()
{
    vector<string> data;
    string line;
    stringstream ss;
    const string file = "InsultsSource.txt";
    ifstream fileIn(file);

    // checks that the file can be opened
    if (fileIn.fail())
    {
        throw FileException("FILE CANNOT BE OPENED!");
    }

    // reads the insults text file and separates the insults
    while (getline(fileIn, line))
    {
        ss.clear();
        ss.str(" ");
        ss << line;
        while (ss >> line)
        {
            data.push_back(line);
        }
    }

    fileIn.close();

    // puts the insults into vectors based on the column they were in
    for (int i = 0; i < data.size(); i += 3)
    {
        col1.push_back(data[i]);
        col2.push_back(data[i + 1]);
        col3.push_back(data[i + 2]);
    }
} // initialize

int InsultGenerator::randGen(const vector<string> &vec)
{
    return (rand() % vec.size());
} // randGen

string InsultGenerator::talkToMe()
{
    return generate(1).at(0);
} // talkToMe

vector<string> InsultGenerator::generate(const int &n)
{
    vector<string> genInsults;

    // check that the number of requested insults is in the specified bounds
    if (n < 1 || n > 10000)
    {
        throw NumInsultsOutOfBounds("THE NUMBER OF REQUESTED INSULTS IS OUT OF BOUNDS! MAX: 10000, MIN: 1");
    }

    // ensures that rand() generates random values
    srand(time(NULL));

    // places the randomly generated insults into a set to assure they are all unique and alphabetically ordered
    set<string> iSet;
    while (iSet.size() < n)
    {
        iSet.insert("Thou " + col1.at(randGen(col1)) + " " + col2.at(randGen(col2)) + " " + col3.at(randGen(col3)) + "!");
    }

    // turns the insult set into a vector
    genInsults.assign(iSet.begin(), iSet.end());

    return genInsults;
} // generate

void InsultGenerator::generateAndSave(const string &str, const int &n)
{

    ofstream fileOut(str);

    // checks that the file can be created
    if (fileOut.fail())
    {
        throw FileException("FILE CANNOT BE CREATED!");
    }

    // check that the number of requested insults is in the specified bounds
    if (n < 1 || n > 10000)
    {
        throw NumInsultsOutOfBounds("THE NUMBER OF REQUESTED INSULTS IS OUT OF BOUNDS! MAX: 10000, MIN: 1");
    }

    // generated insults
    vector<string> vGenSave = generate(n);

    // save the insults to a new file
    for (int i = 0; i < n; i++)
    {
        fileOut << vGenSave.at(i) << endl;
    }

    fileOut.close();

    return;
} // generateAndSave
