/*

CMPE320 Assignment 3
Implementation File
*/

#include <string>
#include <iostream>
#include <ctime>
#include "jumble.h"
using namespace std;

// BadJumbleException constructor
BadJumbleException::BadJumbleException(const string &m) : message(m) {}

string &BadJumbleException::what()
{
    return message;
} // what()

// The jumble puzzle constructor
JumblePuzzle::JumblePuzzle(const string &word, const string &difficulty) : hiddenWord(word), wordLength(word.length())
{

    if (!checkCaseAndAlphabet()) // checks that the word is lowercase and has no special characters
        throw BadJumbleException("ERROR: The hidden word must be all lowercase and may only have alphabetical characters!");

    if (difficulty == "easy") // checking that the input difficulty is valid and setting diff
        diff = 2;
    else if (difficulty == "medium")
        diff = 3;
    else if (difficulty == "hard")
        diff = 4;
    else
        throw BadJumbleException("\nERROR: The difficulty input must be \"easy\", \"medium\" or \"hard\"!");

    if ((wordLength < 3) || (wordLength > 10)) // checking that the word is within the allowed number of characters
        throw BadJumbleException("ERROR: The hidden word must be 3-10 characters long!");
    else
        size = wordLength * diff; // setting size

    genJum(); // generate the jumble puzzle

} // JumblePuzzle()

// The copy constructor
JumblePuzzle::JumblePuzzle(const JumblePuzzle &jp)
{
    size = jp.getSize();
    row = jp.getRowPos();
    col = jp.getColPos();
    dir = jp.getDirection();
    diff = jp.diff;
    hiddenWord = jp.hiddenWord;
    wordLength = jp.wordLength;
    jumPuz = copyJum(jp.getJumble(), jp.getSize());
} // JumblePuzzle() ; copy constructor

// Null Constructor for the Jumble Puzzle
JumblePuzzle::JumblePuzzle()
{
    size = 0;
    row = 0;
    col = 0;
    dir = '\0';
    diff = 0;
    hiddenWord = "\0";
    wordLength = 0;
    jumPuz = nullptr;
} // JumblePuzzle() ; Null Constructor

// The destructor for the Jumble Puzzle
JumblePuzzle::~JumblePuzzle()
{
    deleteJum();
} //~JumblePuzzle()

JumblePuzzle &JumblePuzzle::operator=(const JumblePuzzle &jpRight)
{
    if (this != &jpRight)
    {
        deleteJum();
        size = jpRight.getSize();
        row = jpRight.getRowPos();
        col = jpRight.getColPos();
        dir = jpRight.getDirection();
        diff = jpRight.diff;
        hiddenWord = jpRight.hiddenWord;
        wordLength = jpRight.wordLength;
        jumPuz = copyJum(jpRight.getJumble(), jpRight.getSize());
    }
    return *this;
}

// Returns false is the word is not all lower case and/or has non-alphabetic characters, else returns true
bool JumblePuzzle::checkCaseAndAlphabet()
{
    for (int i = 0; i < wordLength; i++)
    {
        if (isupper(hiddenWord[i]) || !isalpha(hiddenWord[i]))
            return false;
    }
    return true;
} // checkCaseAndAlphabet

// Makes a copy of the jumble puzzle
charArrayPtr *JumblePuzzle::copyJum(const charArrayPtr *jumOther, const int sizeOther) const
{
    charArrayPtr *jumNew = new charArrayPtr[sizeOther]; // generate the pointers
    for (int i = 0; i < sizeOther; i++)
        jumNew[i] = new char[sizeOther]; // generate the 1D char arrays corresponding to the generated pointers

    for (int r = 0; r < sizeOther; r++)
    {
        for (int c = 0; c < sizeOther; c++)
            jumNew[r][c] = jumOther[r][c]; // copy to the new jumble puzzle
    }
    return jumNew;
} // copyJum()

// Deletes the Jumble Puzzle
void JumblePuzzle::deleteJum()
{
    for (int i = 0; i < size; i++)
        delete[] jumPuz[i];
    delete[] jumPuz;
    jumPuz = nullptr;
} // deleteJum()

// generate the jumble puzzle and set row, col, and dir
void JumblePuzzle::genJum()
{
    jumPuz = new charArrayPtr[size]; // generate the pointers
    for (int i = 0; i < size; i++)
        jumPuz[i] = new char[size]; // generate the 1D char arrays corresponding to the generated pointers

    srand(time(NULL));
    for (int r = 0; r < size; r++) // here we populate the 2D jumble puzzle with random characters
    {
        for (int c = 0; c < size; c++)
        {
            jumPuz[r][c] = 'a' + rand() % 26; // generates a random int b/w 0 and 25
        }
    }

    string wordDirection = "nesw";
    int randDir = rand() % wordDirection.length(); // generate a random index for the direction of the word

    int randRow = rand() % size; // generate the initial random row index
    int randCol = rand() % size; // generate the initial random column index

    dir = wordDirection.at(randDir); // use the randomly generated orientation found outside of the loop

    // checking that the word fits in the randomly generated location with the random orientation and placing it in the grid accordingly
    if (dir == 'n') // North case
    {
        randRow = (wordLength - 1) + rand() % (size - wordLength + 1); // generate a random row index in the appropriate range
        for (int r = (randRow - wordLength + 1); r < randRow + 1; r++) // puts the hidden word in the puzzle in the North orientation
            jumPuz[r][randCol] = hiddenWord.at(randRow - r);
    }
    else if (dir == 's') // South case
    {
        randRow = rand() % (size - wordLength + 1);            // generate a random row index in the appropriate range
        for (int r = randRow; r < (randRow + wordLength); r++) // puts the hidden word in the puzzle in the South orientation
            jumPuz[r][randCol] = hiddenWord.at(r - randRow);
    }
    else if (dir == 'e') // East case
    {
        randCol = rand() % (size - wordLength + 1);            // generate a random column index in the appropriate range
        for (int c = randCol; c < (randCol + wordLength); c++) // puts the hidden word in the puzzle in the East orientation
            jumPuz[randRow][c] = hiddenWord.at(c - randCol);
    }
    else if (dir == 'w') // West case
    {
        randCol = (wordLength - 1) + rand() % (size - wordLength + 1); // generate a random column index in the appropriate range
        for (int c = (randCol - wordLength + 1); c < randCol + 1; c++) // puts the hidden word in the puzzle in the West orientation
            jumPuz[randRow][c] = hiddenWord.at(randCol - c);
    }
    row = randRow;
    col = randCol;
    return;
} // genJum()

// accessor for the size of the jumble puzzle
int JumblePuzzle::getSize() const
{
    return size;
} // getSize()

// accessor for the row the hidden word is located in
int JumblePuzzle::getRowPos() const
{
    return row;
} // getRowPos()

// accessor for the column the hidden word is located in
int JumblePuzzle::getColPos() const
{
    return col;
} // getColPos

// accessor for the direction the hidden word is oriented in
char JumblePuzzle::getDirection() const
{
    return dir;
} // getDirection()

// accessor for the jumble puzzle
charArrayPtr *JumblePuzzle::getJumble() const
{
    return copyJum(jumPuz, size);
} // getJumble()
