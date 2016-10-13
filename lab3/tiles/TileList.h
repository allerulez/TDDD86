// A header to define all the required functions of a TileList class.

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"
#include <vector>

class TileList {
public:
    // Constructor
    TileList();
    // Destructor
    ~TileList();
    // Add a tile to the end of the vector
    void addTile(Tile tile);
    // Draw all tiles in the vector to the scene
    void const drawAll(QGraphicsScene* scene);
    // Return the index of the top tile that "covers" (x, y)
    int const indexOfTopTile(int x, int y);
    // Moves a tile to the front of the vector
    void lower(int x, int y);
    // Moves a tile to the back of the vector
    void raise(int x, int y);
    // Removes a tile from the vector
    void remove(int x, int y);
    // Remoes all tiles that "cover" (x, y)
    void removeAll(int x, int y);

private:
    // Contains all tiles
    vector<Tile> tileVector;



};

#endif // TILELIST_H
