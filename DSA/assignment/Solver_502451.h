#ifndef SOLVER_H
#define SOLVER_H

#include "maze_502451.h"
#include <stack>
#include <fstream>

class Solver {
private:
    Maze& maze;
    bool visited[MAX_ROWS][MAX_COLS];
    Point parent[MAX_ROWS][MAX_COLS];

    bool isValid(int r, int c);

public:
    Solver(Maze& m);
    bool solve();
    void writeParentArrayToCSV(const string& filename);
};

#endif
