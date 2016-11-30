
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

using namespace std;

string playerChooseBoard() {
    static string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout << "Please insert 16 letters to represent the board: "<< endl;
    string input = "";
    bool properInput = false;
    while(!properInput) {
        cin>> input;
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        if (input.length() == 16) {
            for (char c: input) {
                properInput = true;
                if(alphabet.find(c) == string::npos) {
                    properInput = false;
                    break;
                }
            }
        }
    }
    return input;
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    static string randomOrChoose = "Would you like to choose the board setup yourself?";
    if(yesOrNo(randomOrChoose)) {
        boggle.resetMan(playerChooseBoard());
    } else {
        boggle.resetRand();
    }
    //Start loop here
    while(true) {
        clearConsole();
        cout<< boggle.curBoard()<<endl;
        cout << "Your words: (" << boggle.playerWords.size() <<"): {";
        for(string word: boggle.playerWords) {
            cout << " '" << word << "',";
        }
        cout << '}' << endl;
        cout << "Your score: " << boggle.playerScore << endl;
        cout << "Type a word or press Enter to end your turn: " <<endl;
        string input="";
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        if(input == "") {
            break;
        }
        if (boggle.tryAddPlayerWord(input)) {
            cout << "You found a new word! " << input << endl;
        }
    }
    cout << "It's my turn!" << endl;
    cout << "My words: (" << boggle.possibleWords.size() << "): ";
    cout << boggle.printSet() << endl;
    cout << "My score: " << boggle.compScore << endl;
    if (boggle.compScore > boggle.playerScore) {
        cout << "ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    } else {
        cout << "It appears you have won. It will not happen again, puny human." << endl;
    }



}

