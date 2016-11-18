// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

char Boggle::rollDie(string die) {
    int charNr = rand() % 6;
    return die[charNr];
}

Boggle::Boggle() {

}


Boggle::~Boggle() {

}

bool Boggle::isWord(string word) {
    return lex.contains(word);
}

bool Boggle::isReqLength(string word) {
    return(word.length()>=4);
}

string Boggle::curBoard() {
    string boardStr="";
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            boardStr+= '[' + board[i][j] + "] ";
        }
        boardStr+="\n";
    }

    return boardStr;
}

void Boggle::resetMan(string dice) {
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            board[i][j] = dice[4*i + j];
        }
    }
}

void Boggle::resetRand() {
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            string temp = CUBES[4*i + j];
            board[i][j] = rollDie(temp);
        }
    }
    shuffle(board);
}

