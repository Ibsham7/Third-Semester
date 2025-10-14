#include "Solver_502451.h"

Solver::Solver(Maze& m) : maze(m) {
    int rows = maze.getRows();
    int cols = maze.getCols();
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            visited[r][c] = false;
            parent[r][c] = Point(-1, -1);
        }
    }
}

bool Solver::isValid(int r, int c) {
    return (r >= 0 && r < maze.getRows() && c >= 0 && c < maze.getCols()
            && maze.getCell(r, c) != '#' && !visited[r][c]);
}

bool Solver::solve() {
    stack<Point> st;
    Point start = maze.getStart();
    Point goal = maze.getGoal();

    st.push(start);
    visited[start.row][start.col] = true;

    int dr[4] = {-1, 1, 0, 0}; // Up, Down, Left, Right
    int dc[4] = {0, 0, -1, 1};

    while (!st.empty()) {
        Point curr = st.top();
        st.pop();

        if (curr.row == goal.row && curr.col == goal.col) {
            // Path found – backtrack
            Point p = goal;
            while (!(p.row == start.row && p.col == start.col)) {
                if (maze.getCell(p.row, p.col) != 'G')
                    maze.setCell(p.row, p.col, '*');
                p = parent[p.row][p.col];
            }
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nr = curr.row + dr[i];
            int nc = curr.col + dc[i];
            if (isValid(nr, nc)) {
                visited[nr][nc] = true;
                parent[nr][nc] = curr;
                st.push(Point(nr, nc));
            }
        }
    }
    return false;
}

void Solver::writeParentArrayToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error writing file: " << filename << endl;
        return;
    }

    int rows = maze.getRows();
    int cols = maze.getCols();

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            Point p = parent[r][c];
            file << "(" << p.row << "," << p.col << ")";
            if (c < cols - 1)
                file << ",";
        }
        file << endl;
    }

    file.close();
}
