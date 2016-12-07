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
    bool isWord(const string &word);
    bool isReqLength(const string &word);
    int playerScore, compScore;
    vector<string> playerWords;
    string curBoard();
    Grid<bool> falseGrid();
    unordered_set<string> searchWords(Grid<bool> &usedLetter, const int x, const int y, string curWord);
    void findAllWords();
    void resetStats();
    void resetRand();
    void resetMan(const string &dice);
    bool tryAddPlayerWord(const string &word);
    string printSet();
    unordered_set<string> possibleWords;
private:
    char rollDie(const string &die);
    Grid<char> board = Grid<char>(BOARD_SIZE, BOARD_SIZE);
    const Lexicon lex = Lexicon(DICTIONARY_FILE);

};

#endif
