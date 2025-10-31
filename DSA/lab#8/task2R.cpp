#include <iostream>
using namespace std;

#define MAX 10

int N;
int board[MAX][MAX];
int solutionCount = 0;

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

void solveNQueens(int row) {
    if (row == N) {
        printBoard();
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;   // Place queen
            solveNQueens(row + 1); // Recurse for next row
            board[row][col] = 0;   // Backtrack
        }
    }
}

int main() {
    cout << "Enter number of Queens (N): ";
    cin >> N;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    solveNQueens(0);

    if (solutionCount == 0)
        cout << "\nNo solution found for " << N << " Queens.\n";
    else
        cout << "\nTotal solutions: " << solutionCount << endl;

    return 0;
}
