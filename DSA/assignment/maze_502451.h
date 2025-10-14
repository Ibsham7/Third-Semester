#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 100;

struct Point {
    int row, col;
    Point(int r = -1, int c = -1) : row(r), col(c) {}
};

class Maze {
private:
    char grid[MAX_ROWS][MAX_COLS];
    int rows, cols;
    Point start, goal;

public:
    Maze();

    bool loadFromFile(const string& filename);
    void printMaze() const;

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    Point getStart() const { return start; }
    Point getGoal() const { return goal; }

    char getCell(int r, int c) const;
    void setCell(int r, int c, char val);
};

#endif
