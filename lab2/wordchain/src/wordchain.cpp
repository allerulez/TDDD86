#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

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

stack<string> wordChain(string w1,string w2) {
    set<string> dictionary = getDictionary(w1.length());
    set<string> seenWords;
    queue<stack<string>> wordQueue;
    stack<string> first;
    stack<string> topStack;
    first.push(w1);
    seenWords.insert(w1);
    wordQueue.push(first);
    while (!wordQueue.empty()) {
        topStack = wordQueue.front();
        wordQueue.pop();
        if(topStack.top() == w2) {

            return topStack;
        } else {
            for (int i = 0; i < w1.length(); i++) {
                for (int j = 0; j < ALPHABET.length(); j++){
                    string tempWord = topStack.top();
                    tempWord[i] = ALPHABET[j];
                    if(dictionary.find(tempWord) != dictionary.end()){
                       if (seenWords.find(tempWord) == seenWords.end()) {
                           seenWords.insert(tempWord);
                           stack<string> newStack = topStack;
                           newStack.push(tempWord);
                           wordQueue.push(newStack);
                       }
                    }        
                }
            }

        }
    }
    return topStack;
}

void print(stack<string> words) {
    while (!words.empty()) {
        cout << words.top();
        words.pop();
        if (!words.empty()) {
            cout << "-->";
        }
    }
    cout.flush();
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    string words;
    string w1, w2;
    bool firstWord = true;
    char letter;
    getline(cin, words);
    for (int i = 0; i < words.length(); i++) {
        letter = words[i];
        if (letter != ' ') {
            if (firstWord) {
                w1 += letter; //.append(letter);
            } else {
                w2 += letter; //.append(letter);
            }
        } else {
            firstWord = false;
        }
    }

    stack<string> wordStack = wordChain(w1, w2);

    print(wordStack);
    cout.flush();
    return 0;
}
