#include <iostream>
#include <stack>
using namespace std;

#define MAX 10

int N;
int board[MAX][MAX];
int solutionCount = 0;

struct Frame {
    int row;
    int col;
};

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i][col] == 1)
            return false;

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;

    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j] == 1)
            return false;

    return true;
}

void printBoard() {
    solutionCount++;
    cout << "\nSolution " << solutionCount << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

void solveIterative() {
    stack<Frame> S;
    int row = 0, col = 0;

    while (true) {
        bool placed = false;
        while (col < N) {
            if (isSafe(row, col)) {
                board[row][col] = 1;
                S.push({row, col});
                placed = true;
                row++;
                col = 0; // reset for next row
                break;
            }
            col++;
        }

        if (row == N) {
            printBoard();
            // Backtrack
            Frame top = S.top();
            S.pop();
            row = top.row;
            col = top.col;
            board[row][col] = 0;
            col++; 
            continue;
        }

        if (!placed) {
            if (S.empty())
                break; // all possibilities exhausted

            Frame top = S.top();
            S.pop();
            row = top.row;
            col = top.col;
            board[row][col] = 0;
            col++;
        }
    }
}

int main() {
    cout << "Enter number of Queens (N): ";
    cin >> N;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    solveIterative();

    if (solutionCount == 0)
        cout << "\nNo solution found for " << N << " Queens.\n";
    else
        cout << "\nTotal solutions: " << solutionCount << endl;

    return 0;
}
