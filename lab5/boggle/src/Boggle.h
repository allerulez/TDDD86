// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <lexicon.h>
#include <unordered_set>
#include <grid.h>
// TODO: include any other header files you need

using namespace std;

class Boggle {

public:
    Boggle ();
    ~Boggle ();
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    static const int BOARD_SIZE = 4;
    bool isWord(string word);
    bool isReqLength(string word);
    string curBoard();
    void resetRand();
    void resetMan(string dice);

private:
    char rollDie(string die);
    Grid<char> board = Grid<char>(BOARD_SIZE, BOARD_SIZE);
    const Lexicon lex = Lexicon(DICTIONARY_FILE);
    unordered_set<string> curWords;


};

#endif
