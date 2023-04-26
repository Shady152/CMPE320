/*

CMPE320 Assignment 3
Header File
*/

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

typedef char *charArrayPtr;

class JumblePuzzle
{
public:
    JumblePuzzle(const string &, const string &); // Constructor generates the Jumble Puzzle
    JumblePuzzle(const JumblePuzzle &);           // Copy Constructor
    JumblePuzzle();                               // Null Constructor
    ~JumblePuzzle();                              // Destructor

    charArrayPtr *getJumble() const;               // get the jumble puzzle
    int getSize() const;                           // gets the size of the jumble puzzle
    int getRowPos() const;                         // gets the row the hidden word is in
    int getColPos() const;                         // gets the column that the hidden word is in
    char getDirection() const;                     // gets the direction that the hidden word is in
    JumblePuzzle &operator=(const JumblePuzzle &); // overloaded assignment operator

private:
    string hiddenWord;                                              // the hidden word
    int wordLength;                                                 // the size of the hidden word
    int size;                                                       // size of the puzzle
    int row;                                                        // row where the hidden word is located
    int col;                                                        // column where the hidden word is located
    char dir;                                                       // orientation of the hidden word
    int diff;                                                       // integer difficulty of the hidden word
    charArrayPtr *jumPuz;                                           // the jumble puzzle
    void genJum();                                                  // generates the jumble puzzle and sets row, col, and dir
    bool checkCaseAndAlphabet();                                    // checks that the hidden word is in all lowercase and has no special characters
    charArrayPtr *copyJum(const charArrayPtr *jp, const int) const; // copy the array elements of one jumble to another
    void deleteJum();                                               // deletes the jumble puzzle
};

// add the unit tests supplied to this class
class BadJumbleException
{
public:
    BadJumbleException(const string &);
    string &what();

private:
    string message;
};