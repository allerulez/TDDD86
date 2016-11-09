#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <tuple>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/**
 * @brief getDictionary reads a dictionary from a text file.
 * @param wordLength is the length of the word to be guessed.
 * @return a set with all words of length wordLength.
 */

set <string> getDictionary(int wordLength) {
    ifstream input;
    input.open("dictionary.txt");
    string line;
    set<string> dict;
    while (input >> line) {
        dict.insert(line);
    }
    return dict;
}


/**
 * @brief print prints the content of a stack.
 * @param words is the stack to be printed.
 */

void print(stack<string> &words) {
    while (!words.empty()) {
        cout << words.top();
        words.pop();
        if (!words.empty()) {
            cout << "-->";
        }
    }
    cout << endl;
}

/**
 * @brief generateChain adds a stack of strings to queue for every viable neighbour word english word
 * @param w1 bottom word in stack
 * @param topStack stack which will be copied and words will be added
 * @param seenWords a set of strings with words already been added
 * @param dictionary is a set of all english words
 * @param wordQueue is where the stacks will be added
 */
void generateChain (const string &w1, const stack<string> &topStack, set<string> &seenWords, const set<string> &dictionary, queue<stack<string>> &wordQueue) {
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

/**
 * @brief wordChain uses an algorithm to determine the shortest transformation path
 * between two given words in a dictionary.
 * @param w1 is the first word.
 * @param w2 is the seond word.
 * @return the stack containing this shortest path.
 */

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
            generateChain(w1, topStack, seenWords, dictionary, wordQueue);

        }
    }
    return topStack;
}


/**
 * @brief getInput reads input from the terminal.
 * @return the words input as a tuple of strings.
 */

tuple<string, string> getInput() {
    string w1, w2;
    cin >> w1 >> w2;
    return make_tuple(w1, w2);
}

/**
 * @brief main is the main function calling all other functions when needed.
 * @return successful run
 */

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    tuple<string, string> words = getInput();
    stack<string> wordStack = wordChain(get<0>(words), get<1>(words));

    print(wordStack);
    cout.flush();
    return 0;
}
