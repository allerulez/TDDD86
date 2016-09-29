// TDDD86 aleev379 robka246
// This is a simple implementation of the "Game of Life"


#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include "fstream"

using namespace std;


/**

 * @brief countNeighbour is a function that counts the number of neighbours
 * a given coordinate in the given "grid" has.
 * @param grid is a representation of the playing field.
 * @param x
 * @param y
 * @return the amount of neighbours of the coordinate (x, y)
 */
int countNeighbour(Grid<char>& grid, int x, int y) {
    int neighbours = 0;
    for(int row = x-1; row<=x+1; row++ ) {
        for(int col=y-1; col<=y+1; col++) {
            if (grid.inBounds(row, col) && grid.get(row, col)=='X') {
                neighbours++;
                if(row==x && col == y) {
                    neighbours--;
                }
            }
        }
    }

    return neighbours;
}

/**
 * @brief tick is a function that updates the grid one lifecycle
 * according to the rules of the game of life.
 * @param grid is the grid used to represent the playing field.
 **/
void tick(Grid<char>& grid) {
    Grid<char> tempGrid = grid;
    for(int i = 0; i < grid.numRows(); i++) {
        for(int j = 0; j < grid.numCols(); j++) {
            int neighbours = countNeighbour(tempGrid, i, j);
            if (neighbours < 2 or neighbours > 3) {
                grid.set(i, j, '-');
            } else if(neighbours == 3) {
                grid.set(i, j, 'X');
            }
            neighbours = 0;
        }
    }
}

/**
 * @brief print is a function used to output to the terminal.
 * @param grid is the grid to be printed.
 */
void print(const Grid<char> &grid) {
    for(int i = 0; i < grid.numRows(); i++) {
        for(int j = 0; j < grid.numCols(); j++) {
            cout << grid.get(i,j);
        }
        cout << endl;
    }
}

/**
 * @brief animate is a function used when continuously updating the grid
 * in the terminal.
 * @param grid is the grid to work with.
 */
void animate(Grid<char>& grid) {
    bool animating = true;
    while(animating) {
        tick(grid);
        print(grid);
        pause(100);
        clearConsole();
    }
}

/**
 * @brief readGrid is a function that reads the grid to be used from a
 * text file.
 * @param args contains the name of the text file.
 * @return the grid.
 */
Grid<char> readGrid(char* args[]) {
    ifstream input;
    input.open(args[1]);
    string line;
    getline(input, line);
    int rows = stoi(line);
    getline(input, line);
    int cols = stoi(line);
    Grid<char> grid = Grid<char>(rows, cols);
    for(int i = 0; i < rows; i++) {
        getline(input, line);
        for(int j = 0; j < cols; j++) {
            grid.set(i, j, line[j]);
        }
    }
    return grid;
}

/**
 * @brief main is the main function containing the game loop.
 * @param argc unchanged
 * @param args unchanged
 * @return successfully run
 */
int main(int argc, char* args[]) {

    bool running = true;
    string userinput;
    Grid<char> grid = readGrid(args);
    print(grid);
    while (running) {
        cout << "a)nimate, t)ick, q)uit?" << endl ;
        cin >> userinput;
        if(userinput == "a") {
            animate(grid);
        }else if(userinput == "t"){
            tick(grid);
            print(grid);
        }else if( userinput == "q") {
            running=false;
        }
    }

    cout << "Have a nice Life!" << endl;
    return 0;
}

