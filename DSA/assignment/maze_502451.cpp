#include "maze_502451.h"
#include <fstream>
#include <sstream>

Maze::Maze() {
    rows = cols = 0;
}

bool Maze::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    rows = 0;
    while (getline(file, line) && rows < MAX_ROWS) {
        stringstream ss(line);
        string cell;
        int c = 0;

        while (getline(ss, cell, ',') && c < MAX_COLS) {
            char ch = (cell.empty()) ? ' ' : cell[0];
            grid[rows][c] = ch;

            if (ch == 'S')
                start = Point(rows, c);
            else if (ch == 'G')
                goal = Point(rows, c);

            c++;
        }
        cols = c;
        rows++;
    }
    file.close();
    return true;
}

void Maze::printMaze() const {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << grid[r][c] << ' ';
        }
        cout << endl;
    }
}

char Maze::getCell(int r, int c) const {
    return grid[r][c];
}

void Maze::setCell(int r, int c, char val) {
    grid[r][c] = val;
}
