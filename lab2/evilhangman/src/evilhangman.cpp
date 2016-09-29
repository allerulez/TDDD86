#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/**
 * @brief getDictionary Fetch the words of length wordLength from a text file.
 * @param wordLength
 * @return Vector containing the words.
 */
vector <string> getDictionary(int wordLength) {
    ifstream input;
    input.open("dictionary.txt");
    string line;
    string tempWord = "";
    bool empty=false;
    vector<string> dict;
    while (!empty) {
        getline(input, line);
        if (line.length() == 0 || tempWord == line) {
            empty = true;
        } else if (line.length() == wordLength){
            dict.insert(dict.end(), line);
        }
        tempWord = line;
    }

    return dict;
}

/**
 * @brief createKeyList Builds a vector containing all the possible key variants
 * based on the current word and the guess.
 * @param curWord Current word.
 * @param letter The guessed letter.
 * @return The vector.
 */
vector<string> createKeyList(string curWord, const char letter) {
    vector<string> theSet;
    queue<string> wordQueue;
    string letterString = "";
    letterString += letter;
    if(curWord.at(0) != '-'){
        letterString = curWord[0];
        wordQueue.push(letterString);
    }
    else{
        wordQueue.push("-");
        wordQueue.push(letterString);
    }
    while (!wordQueue.empty()){
        string firstElement = wordQueue.front();
        if(firstElement.length() == curWord.length()){
            theSet.insert(theSet.end(), firstElement);
        }
        else if(curWord.at(firstElement.length()) == '-'){
            string elementCopy = firstElement;
            elementCopy += "-";
            firstElement += letter;
            wordQueue.push(elementCopy);
            wordQueue.push(firstElement);
        }
        else{
            firstElement += curWord[firstElement.length()];
            wordQueue.push(firstElement);
        }
        wordQueue.pop();
    }
    return theSet;
}
/**
 * @brief wordClassSort Sorts words from dict into wordMap based on suitable keys.
 * @param dict Vector containing all remaining words.
 * @param wordMap Map of pairs of Keys and Vectors.
 * @param keyList Vector of all Keys in wordMap.
 * @param letter The guessed letter.
 */
void wordClassSort (vector<string> const dict, map<string, vector<string>> &wordMap, vector<string> const keyList, char const letter) {
    for (string w: dict) {
        for (string key: keyList) {
            for (int i = 0; i<w.length(); i++) {
                if (w[i] == key[i] || (key[i] == '-' && w[i] != letter)) {
                    if (i == w.length()-1) {
                        wordMap[key].insert(wordMap[key].end(), w);
                    }
                } else {
                    break;
                }
            }
        }
    }
}
/**
 * @brief wordClassSize Compares the sizes of all vectors in wordMap.
 * @param wordMap Map of all keys and word vectors.
 * @return Pair of the largest vector and its key.
 */
pair<string, vector<string>> wordClassSize (map<string, vector<string>> const wordMap) {
    string key = wordMap.begin()->first;
    for (auto const &pair: wordMap) {
        if (pair.second.size() > wordMap.at(key).size()) {
            key = pair.first;
        }
    }
    return pair<string, vector<string>> (key, wordMap.at(key));

}

/**
* @brief main Contains the game loop.
* @return Successful run.
*/
int main() {
    bool playing = true;
    while (playing) {
        // Initialisation, get input required to setup
        bool correct = false;
        cout << "Welcome to Hangman." << endl;
        int wordLength, currentGuess;
        vector<string> dict;
        string currentWord, usedLetters;
        while (dict.empty()) {
            cout << "Please input word length:";
            cin >> wordLength;
            dict = getDictionary(wordLength);
        }
        for (int i = 0; i < wordLength; i++) {
            currentWord += '-';
        }
        cout << "Please input the maximum number of guesses:";
        cin >> currentGuess;
        // The main game loop that calls all required functions.
        while (currentGuess > 0 && !correct) {
            string currentLetter;
            cout << "The current word: " << currentWord << endl;
            cout << "Guesses left: " << currentGuess << endl;
            cout << "Guessed letters: " << usedLetters << endl;
            cout << "Please input your next guess: ";
            cin >> currentLetter;
            size_t found = ALPHABET.find(currentLetter[0]);
            size_t found2 = usedLetters.find(currentLetter[0]);
            size_t length = currentLetter.length();
            if (length == 1 &&  found != string::npos &&
             found2 == string::npos) {
                usedLetters += currentLetter[0];
                vector<string> keyList = createKeyList(currentWord, currentLetter[0]);
                map<string, vector<string>> wordMap;
                for (string w: keyList) {
                    vector<string> emptyList;
                    wordMap.insert(pair<string, vector<string>>(w, emptyList));
                }
                wordClassSort(dict, wordMap, keyList, currentLetter[0]);
                pair<string, vector<string>> largestDict = wordClassSize(wordMap);
                dict = largestDict.second;
                currentWord = largestDict.first;
                currentGuess--;
                if (dict.size() == 1 && dict.front() == currentWord) {
                    correct=true;

                }
            }
        }
        if (correct) {
            cout << "Congratulations, the word was '"<<currentWord<<"'!"<<endl;
        } else {
            cout << "You lost!"<<endl;
        }
        bool badInput = true;
        while (badInput) {
            cout << "Would you like to play again? (y)es , (n)o: ";
            string answer;
            cin >> answer;
            if (answer == "y") {
                badInput = false;
            } else if (answer == "n") {
                badInput = false;
                playing = false;
            }

        }
    }
    return 0;
}
