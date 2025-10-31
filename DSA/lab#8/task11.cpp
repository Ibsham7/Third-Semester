#include <iostream>
using namespace std;

#define MAX 10

bool goalFound = false;

void copyBoard(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

bool isEqual(int a[], int b[], int n) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i]) return false;
    return true;
}

void printBoard(int board[], int n) {
    for (int i = 0; i < n; i++) {
        if (board[i] == 1) cout << "B ";
        else if (board[i] == 2) cout << "W ";
        else cout << "_ ";
    }
    cout << endl;
}

void solveRecursive(int board[], int goal[], int n, int depth) {
    // Check if goal reached
    if (isEqual(board, goal, n)) {
        cout << "\nGoal reached!\n\n";
        for (int i = 0; i <= depth; i++)
            cout << "Move " << i + 1 << ": ";
        printBoard(board, n);
        goalFound = true;
        return;
    }

    if (goalFound) return; 


    for (int i = 0; i < n; i++) {
        if (goalFound) return;

        if (board[i] == 1) { 
            // Step move
            if (i + 1 < n && board[i + 1] == -1) {
                int temp[MAX];
                copyBoard(temp, board, n);
                swap(temp[i], temp[i + 1]);

                cout << "Move " << depth + 1 << ": ";
                printBoard(temp, n);
                solveRecursive(temp, goal, n, depth + 1);
            }
            // Jump move
            if (i + 2 < n && board[i + 1] == 2 && board[i + 2] == -1) {
                int temp[MAX];
                copyBoard(temp, board, n);
                swap(temp[i], temp[i + 2]);

                cout << "Move " << depth + 1 << ": ";
                printBoard(temp, n);
                solveRecursive(temp, goal, n, depth + 1);
            }
        }
        else if (board[i] == 2) { 
            // Step move
            if (i - 1 >= 0 && board[i - 1] == -1) {
                int temp[MAX];
                copyBoard(temp, board, n);
                swap(temp[i], temp[i - 1]);

                cout << "Move " << depth + 1 << ": ";
                printBoard(temp, n);
                solveRecursive(temp, goal, n, depth + 1);
            }
            // Jump move
            if (i - 2 >= 0 && board[i - 1] == 1 && board[i - 2] == -1) {
                int temp[MAX];
                copyBoard(temp, board, n);
                swap(temp[i], temp[i - 2]);

                cout << "Move " << depth + 1 << ": ";
                printBoard(temp, n);
                solveRecursive(temp, goal, n, depth + 1);
            }
        }
    }
}

int main() {
    int n = 5; // (2 black + 1 empty + 2 white)
    int start[MAX] = {1, 1, -1, 2, 2};
    int goal[MAX] = {2, 2, -1, 1, 1};

    cout << "Starting Board:\n";
    printBoard(start, n);

    cout << "\nSolving using recursion...\n";
    solveRecursive(start, goal, n, 0);

    if (!goalFound)
        cout << "\nNo solution found.\n";

    return 0;
}
