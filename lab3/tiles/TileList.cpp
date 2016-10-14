#include "TileList.h"

TileList::TileList()
{
    size = 10;
    Tile* tileArray[size];
    curPos=0;
}

TileList::~TileList()
{
    delete [] &tileArray;
}

void TileList::addTile(Tile tile)
{
    if (curPos < size) {
        tileArray[curPos] = tile;
    } else {
        increaseArraySize();
        tileArray[curPos] = tile;
    }
    curPos++;

}

void TileList::increaseArraySize () {
    size*=2;
    Tile newArr[size];
    for (int i=0; i< size/2; i++) {
        newArr[i]= tileArray[i];
    }

    delete [] tileArray;
    tileArray = newArr;
}

void const TileList::drawAll(QGraphicsScene* scene)
{
    for (Tile t: tileVector) {
        t.draw(scene);
    }
}

int const TileList::indexOfTopTile(int x, int y)
{
    for (int i = tileVector.size()-1; i >= 0; i--) {
        if(tileVector[i].contains(x, y)) {
            return i;
        }
    }
    return -1;
}

void TileList::raise(int x, int y)
{
    int tileInd = indexOfTopTile(x, y);
    if ( tileInd != -1) {
        Tile t= tileVector[tileInd];
        tileVector.push_back(t);
        tileVector.erase(tileVector.begin() + tileInd);
    }
}

void TileList::lower(int x, int y)
{
    int tileInd = indexOfTopTile(x, y);
    if ( tileInd != -1) {
        Tile t= tileVector[tileInd];
        tileVector.erase(tileVector.begin() + tileInd);
        tileVector.insert(tileVector.begin(), t);
    }
}

void TileList::remove(int x, int y)
{
    int tileInd = indexOfTopTile(x, y);
    if ( tileInd != -1) {
        tileVector.erase(tileVector.begin() + tileInd);
    }
}

void TileList::removeAll(int x, int y)
{
    while(indexOfTopTile(x,y) != -1) {
        remove(x,y);
    }
}
