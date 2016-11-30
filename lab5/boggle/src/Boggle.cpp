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
            boardStr.append( "[");
            boardStr.push_back(board[i][j]);
            boardStr+= "] ";
        }
        boardStr+="\n";
    }

    return boardStr;
}
Grid<bool> Boggle::falseGrid() {
    Grid<bool> usedLetterBoard = Grid<bool>(BOARD_SIZE, BOARD_SIZE);
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            usedLetterBoard[i][j] = false;

        }
    }
    return usedLetterBoard;
}

unordered_set<string> Boggle::searchWords(Grid<bool> usedLetter, const int x, const int y, string curWord) {
    unordered_set<string> retSet;
    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
            if(i>= 0 && i <BOARD_SIZE && j>= 0 && j <BOARD_SIZE) {
                if (!usedLetter[i][j]) {
                    if (lex.containsPrefix(curWord+board[i][j])) {
                        usedLetter[i][j] = true;
                        unordered_set<string> tempSet = searchWords(usedLetter, i, j, curWord+board[i][j]);
                        retSet.insert(tempSet.begin(), tempSet.end());
                        usedLetter[i][j] = false;

                    }
                }
            }
        }
    }
    if(lex.contains(curWord) && curWord.length()>=4) {
        retSet.insert(curWord);
        compScore+= (curWord.length()-3);
    }
    return retSet;
}

void Boggle::findAllWords() {
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            Grid<bool> usedLetter = falseGrid();
            usedLetter[i][j] = true;
            string tempStr;
            tempStr.push_back(board[i][j]);
            unordered_set<string> temp = searchWords(usedLetter, i, j, tempStr);
            possibleWords.insert(temp.begin(), temp.end());
            usedLetter[i][j] = false;
        }
    }
}

void Boggle::resetStats() {
    playerScore = 0;
    compScore = 0;
    playerWords.clear();
    possibleWords.clear();
}

void Boggle::resetMan(string dice) {
    resetStats();
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            board[i][j] = dice[4*i + j];
        }
    }
    cout<<"asdads"<<endl;
    findAllWords();
}

void Boggle::resetRand() {
    resetStats();
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            string temp = CUBES[4*i + j];
            board[i][j] = rollDie(temp);
        }
    }
    shuffle(board);
    cout<<"asdads"<<endl;
    findAllWords();
}

bool Boggle::tryAddPlayerWord(string word) {
    if(possibleWords.find(word) != possibleWords.end()) {
        possibleWords.erase(word);
        playerWords.push_back(word);
        playerScore += (word.length()-3);
        compScore -= (word.length()-3);
        return true;
    }
    return false;
}

string Boggle::printSet() {
    string retStr = "{ ";
    for(const auto& w: possibleWords) {
        retStr.append("'" + w + "', ");
    }
    retStr.append("}");
    return retStr;
}


