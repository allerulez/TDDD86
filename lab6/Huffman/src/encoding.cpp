#include "queue"
#include "encoding.h"


using namespace std;

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    char c;
    while (input.get(c)) {
        if (freqTable.find(int(c)) != freqTable.end()) {
            freqTable[int(c)] += 1;
        } else {
            freqTable.insert(pair<int,int> (int(c), 1));
        }
    }
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {


    return nullptr;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
