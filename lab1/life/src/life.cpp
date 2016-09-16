// TDDD86 aleev379 robka246
// This is a simple implementation of the "Game of Life"


#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include "fstream"

using namespace std;



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

void print(Grid<char> grid) {
    for(int i = 0; i < grid.numRows(); i++) {
        for(int j = 0; j < grid.numCols(); j++) {
            cout << grid.get(i,j);
        }
        cout << endl;
    }
}

void animate(Grid<char>& grid) {
    bool animating = true;
    while(animating) {
    tick(grid);
    print(grid);
    pause(100);
    clearConsole();
    }
}

int main(int argc, char* args[]) {

    bool running = true;
    ifstream input;
    input.open(args[1]);
    string line;
    string userinput;
    getline(input, line);
    int rows = stoi(line);
    getline(input, line);
    int cols = stoi(line);
    Grid<char> grid = Grid<char>(rows, cols);
    cout << endl;
    for(int i = 0; i < rows; i++) {
        getline(input, line);
        for(int j = 0; j < cols; j++) {
            grid.set(i, j, line[j]);
            cout << line[j];
        }
        cout << endl;
    }
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

