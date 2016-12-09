// TDDD86 aleev379 robka246

#include "queue"
#include "encoding.h"
#include <bitset>

using namespace std;

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    char c;
    while (input.get(c)) {
        freqTable[int(c)] += 1;
    }
    freqTable[256] = 1;
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    auto cmp = [](HuffmanNode* left, HuffmanNode* right){ return left->count > right->count;};
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(cmp)> prioQ(cmp);
    for (pair<int, int> keyPair: freqTable) {
        HuffmanNode* tempNode = new HuffmanNode(keyPair.first, keyPair.second);
        prioQ.push(tempNode);
    }
    while(true) {
        HuffmanNode* firstLeaf = prioQ.top();
        prioQ.pop();
        if (prioQ.empty()) {
            return firstLeaf;
        }
        HuffmanNode* secondLeaf = prioQ.top();
        prioQ.pop();
        HuffmanNode* node = new HuffmanNode(256, firstLeaf->count + secondLeaf->count, firstLeaf, secondLeaf);
        prioQ.push(node);
    }
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    queue<pair<HuffmanNode*, string>> theQueue;
    theQueue.push(pair<HuffmanNode*, string>(encodingTree->zero, "0"));
    theQueue.push(pair<HuffmanNode*, string>(encodingTree->one, "1"));
    while(!theQueue.empty()) {
        pair<HuffmanNode*, string> aPair = theQueue.front();
        if(aPair.first->zero != nullptr) {
            pair<HuffmanNode*, string> newPair =
                    pair<HuffmanNode*, string>(aPair.first->zero, aPair.second + "0");
            theQueue.push(newPair);
        }
        if(aPair.first->one != nullptr) {
            pair<HuffmanNode*, string> newPair =
                    pair<HuffmanNode*, string>(aPair.first->one, aPair.second + "1");
            theQueue.push(newPair);
        } else if(aPair.first->isLeaf()) {
            pair<int, string> newPair =
                    pair<int, string>(aPair.first->character, aPair.second);
            encodingMap.insert(newPair);

        }
        theQueue.pop();
    }

    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    char c;
    while(input.get(c)) {
        string value = encodingMap.at(int(c));
        for(char ch: value) {
            if(ch=='0') output.writeBit(0);
            else if(ch=='1') output.writeBit(1);
        }
    }
    for (char val: encodingMap.at(256)) {
        if(val=='0') output.writeBit(0);
        else output.writeBit(1);
    }

}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int c;
    HuffmanNode* node = encodingTree;
    while(c != EOF) {
        c = input.readBit();
        if (node->isLeaf()) {
            output.put(char(node->character));
            node = encodingTree;
        }
        if(c==0) {
            node = node->zero;
        } else if (c==1) {
            node = node->one;
        }
    }
}

void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    input.clear();
    HuffmanNode* tree = buildEncodingTree(freqTable);
    map<int, string> encMap = buildEncodingMap(tree);
    string mapString = "{";
    for (pair<int, int> aPair: freqTable) {
        for(char c: to_string(aPair.first)) mapString += c;
        mapString += ':';
        for(char c: to_string(aPair.second)) mapString += c;
        mapString += ',';
        mapString += ' ';
    }
    mapString.pop_back();
    mapString.pop_back();
    mapString += '}';

    for (char c: mapString) {
        output.put(c);
    }

    input.seekg(0, input.beg);
    encodeData(input, encMap, output);
    freeTree(tree);
}

void decompress(ibitstream& input, ostream& output) {
    string chars = "";
    char c;
    do {
        input.get(c);
        chars += c;
    }while (c != '}');
    bool beforeCol = true;
    string first = "", second = "";
    map<int, int> freqTable;
    for (char ch: chars) {
        if (ch == ':') {
            beforeCol = !beforeCol;
        } else if(ch == ',' || ch == '}') {
            freqTable[stoi(first)] = stoi(second);
            first = "";
            second = "";
            beforeCol = !beforeCol;

        }else if (beforeCol) {
            if (ch == ' ' || ch == '{') {

            } else {
                first += ch;
            }
        } else {
            second += ch;
        }
    }
    HuffmanNode* tree = buildEncodingTree(freqTable);
    decodeData(input, tree, output);
    freeTree(tree);
}

void freeTree(HuffmanNode* node) {
    if (node->isLeaf()) {
        delete node;
    } else {
        if(node->zero != nullptr) {
            freeTree(node->zero);
        }
        if(node->one != nullptr) {
            freeTree(node->one);
        }
    }
}
