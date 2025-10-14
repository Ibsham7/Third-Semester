#include "maze_502451.h"
#include "Solver_502451.h"
#include <iostream>
using namespace std;

int main() {
    string filename;
    cout << "Enter maze filename (e.g., maze.csv): ";
    cin >> filename;

    Maze maze;
    if (!maze.loadFromFile(filename)) {
        cout << "Failed to load maze file.\n";
        return 1;
    }

    cout << "\nUnsolved Maze:\n";
    maze.printMaze();

    Solver solver(maze);
    if (solver.solve()) {
        cout << "\nSolved Maze:\n";
        maze.printMaze();
        solver.writeParentArrayToCSV("parent_array_output.csv");
        cout << "\nParent array saved to parent_array_output.csv\n";
    } else {
        cout << "\nNo path found from S to G.\n";
    }

    return 0;
}
