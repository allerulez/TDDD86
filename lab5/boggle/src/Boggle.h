// TDDD86 aleev379 robka246

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <vector>
#include <lexicon.h>
#include <unordered_set>
#include <grid.h>

using namespace std;

class Boggle {

public:
    Boggle ();
    ~Boggle ();
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    static const int BOARD_SIZE = 4;
    // returns wether the given string is a word in the dictionary
    bool isWord(const string &word);
    // returns wether the given string is of at least length MIN_WORD_LENGTH
    bool isReqLength(const string &word);
    int playerScore, compScore;
    vector<string> playerWords;
    // returns a printable string representing the current board
    string curBoard();
    // returns a grid of false booleans
    Grid<bool> falseGrid();
    // finds all possible words given a prefix and board position
    unordered_set<string> searchWords(Grid<bool> &usedLetter, const int x, const int y, string curWord);
    // finds all words
    void findAllWords();
    // resets all stats such as found words and score to play a new game
    void resetStats();
    // set a random boggle board to be played
    void resetRand();
    // set the board to the input board
    void resetMan(const string &dice);
    // checks if a user given word is on the board and adds it to the players words
    // returns a bool representing success
    bool tryAddPlayerWord(const string &word);
    // returns a string of all the computers words
    string printSet();
    unordered_set<string> possibleWords;
private:
    // returns a random char from a given string
    char rollDie(const string &die);
    Grid<char> board = Grid<char>(BOARD_SIZE, BOARD_SIZE);
    const Lexicon lex = Lexicon(DICTIONARY_FILE);

};

#endif
