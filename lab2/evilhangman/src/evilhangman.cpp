#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

using mymap = map<string, set>;

set <string> getDictionary(int wordLength) {
    ifstream input;
    input.open("dictionary.txt");
    string line;
    string tempWord = "";
    bool empty=false;
    set<string> dict;
    while (!empty) {
        getline(input, line);
        if (line.length() == 0 || tempWord == line) {
            empty = true;
        } else if (line.length() == wordLength){
            dict.insert(line);
        }
        tempWord = line;
    }

    return dict;
}

set<string> createMap (string curWord, string letter) {
    if (curWord[0] != '-') {
        set<string> tempSet = createMap(curWord.erase(curWord.begin()), letter);
        for(string w :tempSet) {
            w.insert(0, curWord[0]);
        }
    } else {
        set<string> aSet = createMap(curWord.erase(curWord.begin()), letter);
    }

}

set <string> checkWords(set <string> words, string letter, string curWord) {
    mymap wordMap;
    for (int i = 0; i < curWord.length(); i++) {
        string tempWord = curWord;
        if (curWord[i] == '-') {
            tempWord[i] == letter;
            wordMap.insert(tempWord, new set<string>);

        }
    }

    return newDict;
}


int main() {
    cout << "Welcome to Hangman." << endl;
    int wordLength, currentGuess;
    set <string> dict;
    string currentWord, usedLetters;
    while (dict.empty()) {
        cout << "Please input word length:";
        cin >> wordlength;
        dict = getDictionary(wordLength);
    }
    for (int i = 0; i < wordLength; i++) {
        currentWord += '-';
    }

    cout << "Please input the maximum number of guesses:";
    cin >> currentGuess;
    while (currentGuess > 0) {
        string currentletter;
        cout << "The current word: " << currentWord << endl;
        cout << "Guesses left: " << currentGuess << endl;
        cout << "Guessed letters: " << usedLetters << endl;
        cout << "Please input your next guess: ";
        cin << currentletter;
        if (currentLetter.length() == 1 && ALPHABET.find(currentLetter) != string.npos) {
            if (usedLetters.find(currentletter) != string.npos) {
                usedLetters += currentletter;
                dict = checkWords(dict, currentletter, currentWord);
            }
        }
    }
    return 0;
}
