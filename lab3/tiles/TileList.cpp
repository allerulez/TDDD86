#include "TileList.h"

TileList::TileList()
{
    size = 10;
    tileArray = new Tile[size];
    curPos=0;
}

TileList::~TileList()
{
    delete [] tileArray;
}

void TileList::addTile(Tile tile)
{
    if(curPos == size) {
        increaseArraySize();
    }
    tileArray[curPos] = tile;
    curPos++;

}

void TileList::increaseArraySize () {
    size*=2;
    Tile* newArr = new Tile[size];
    for (int i = 0; i < size/2; i++) {
        newArr[i] = tileArray[i];
    }

    delete tileArray;
    tileArray = newArr;
}

void const TileList::drawAll(QGraphicsScene* scene)
{
    for ( int i = 0; i < size-1; i++) {
        tileArray[i].draw(scene);
    }
}

int const TileList::indexOfTopTile(int x, int y)
{
    for (int i = size-1; i >= 0; i--) {
        if(tileArray[i].contains(x, y)) {
            return i;
        }
    }
    return -1;
}

void TileList::raise(int x, int y)
{
    int tileInd = indexOfTopTile(x, y);
    if ( tileInd != -1) {
        Tile t= tileArray[tileInd];
        for (int i = tileInd; i < curPos; i++) {
            tileArray[i] = tileArray[i+1];
        }
        tileArray[curPos] = t;
    }
}

void TileList::lower(int x, int y)
{
    int tileInd = indexOfTopTile(x, y);
    if ( tileInd != -1) {
        Tile t= tileArray[tileInd];
        for (int i = tileInd; i > 0;i--) {
            tileArray[i] = tileArray[i-1];
        }
        tileArray[0] = t;
    }
}

void TileList::remove(int x, int y)
{
    int tileInd = indexOfTopTile(x, y);
    if ( tileInd != -1) {
        for(int i = tileInd; i<curPos; i++){
            tileArray[i] = tileArray[i+1];
        }
        curPos--;
    }
}

void TileList::removeAll(int x, int y)
{
    while(indexOfTopTile(x,y) != -1) {
        remove(x,y);
    }
}
