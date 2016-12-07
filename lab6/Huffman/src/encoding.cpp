#include "queue"
#include "encoding.h"


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
        HuffmanNode* node = new HuffmanNode(257, firstLeaf->count + secondLeaf->count, firstLeaf, secondLeaf);
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
        } else if(aPair.first->zero == nullptr) {
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
    HuffmanNode* tree = buildEncodingTree(freqTable);
    map<int, string> encMap = buildEncodingMap(tree);
    string mapString = "{";
    for (pair<int, string> aPair: encMap) {
        mapString += aPair.first;
        mapString += ":" + aPair.second + ",";
    }
    mapString.pop_back();
    cout << mapString << endl;
    //            erase(mapString.end()-1, mapString.end());
    mapString.append("}");
    for (char c: mapString) {
        output.put(c);
    }
    encodeData(input, encMap, output);

}

void decompress(ibitstream& input, ostream& output) {
    int c=0;
    string charString = "";
     do {
        c = input.readBit();
        charString += c;
    }
    while(c!=int('}'));

    string first;
    string second;
    int key;
    bool beforeCol = true;
    map<int, int> aMap;
    for (char ch: charString) {
        if(ch == '}') break;
        else if(ch == ',') {
            key = stoi(first);
            aMap[key] = stoi(second);
            first = "";
            second = "";
            beforeCol = true;
        } else if (ch == ':') {
            beforeCol = false;
        } /*else if (ch == ' ') {

        }*/ else {
            if (beforeCol) first += ch;
            else second += ch;
        }
    }
    HuffmanNode* ourTree = buildEncodingTree(aMap);
    decodeData(input, ourTree, output);

}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
