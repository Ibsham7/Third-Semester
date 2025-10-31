#include <iostream>
#include <stack>
#include <map>
using namespace std;

#define MAX 10

struct Node {
    int board[MAX];
    int size;
    bool marked;
};

void copyBoard(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
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

string boardToKey(int board[], int n) {
    string key = "";
    for (int i = 0; i < n; i++) {
        key += to_string(board[i]);
        if (i != n - 1) key += ",";
    }
    return key;
}

// Convert key string back to board array
void keyToBoard(string key, int board[], int n) {
    int idx = 0;
    string temp = "";
    for (int i = 0; i < key.size(); i++) {
        if (key[i] == ',' || i == key.size() - 1) {
            if (i == key.size() - 1 && key[i] != ',')
                temp += key[i];
            board[idx++] = stoi(temp);
            temp = "";
        } else {
            temp += key[i];
        }
    }
}

void generateChildren(stack<Node> &S, Node current) {
    int n = current.size;

    for (int i = 0; i < n; i++) {
        if (current.board[i] == 1) { // Black ball moves right
            // Just move one spot
            if (i + 1 < n && current.board[i + 1] == -1) {
                Node child;
                copyBoard(child.board, current.board, n);
                swap(child.board[i], child.board[i + 1]);
                child.size = n;
                child.marked = false;
                S.push(child);
            }
            // Jump
            if (i + 2 < n && current.board[i + 1] == 2 && current.board[i + 2] == -1) {
                Node child;
                copyBoard(child.board, current.board, n);
                swap(child.board[i], child.board[i + 2]);
                child.size = n;
                child.marked = false;
                S.push(child);
            }
        }
        else if (current.board[i] == 2) { // White ball moves left
            // Step
            if (i - 1 >= 0 && current.board[i - 1] == -1) {
                Node child;
                copyBoard(child.board, current.board, n);
                swap(child.board[i], child.board[i - 1]);
                child.size = n;
                child.marked = false;
                S.push(child);
            }
            // Jump
            if (i - 2 >= 0 && current.board[i - 1] == 1 && current.board[i - 2] == -1) {
                Node child;
                copyBoard(child.board, current.board, n);
                swap(child.board[i], child.board[i - 2]);
                child.size = n;
                child.marked = false;
                S.push(child);
            }
        }
    }
}

bool solve(Node start, Node goal) {
    stack<Node> S;
    map<string, string> parent; // child -> parent mapping

    string startKey = boardToKey(start.board, start.size);
    parent[startKey] = "ROOT";

    S.push(start);

    while (!S.empty()) {
        Node &top = S.top();

        bool isLeaf = top.marked;

        if (isLeaf) {
            if (isEqual(top.board, goal.board, top.size)) {
                cout << "\nGoal reached!\n\n";

                // Reconstruct path using parent map
                string key = boardToKey(top.board, top.size);
                string path[200];
                int count = 0;

                while (key != "ROOT") {
                    path[count++] = key;
                    key = parent[key];
                }

                // Print in forward order
                for (int i = count - 1; i >= 0; i--) {
                    int tempBoard[MAX];
                    keyToBoard(path[i], tempBoard, top.size);
                    cout << "Move " << (count - i) << ": ";
                    printBoard(tempBoard, top.size);
                }

                return true;
            } else {
                S.pop();
            }
        } 
        else if (!top.marked) {
            top.marked = true;
            Node current = top;
            string parentKey = boardToKey(current.board, current.size);

            // Generate children temporarily
            stack<Node> temp;
            generateChildren(temp, current);

            while (!temp.empty()) {
                Node child = temp.top();
                temp.pop();

                string childKey = boardToKey(child.board, child.size);
                if (parent.find(childKey) == parent.end()) {
                    parent[childKey] = parentKey;
                    S.push(child);
                }
            }
        }
    }
    return false;
}

int main() {
    Node start, goal;

    start.size = 5;
    int init[5] = {1, 1, -1, 2, 2};
    int target[5] = {2, 2, -1, 1, 1};
    copyBoard(start.board, init, 5);
    copyBoard(goal.board, target, 5);
    start.marked = false;
    goal.marked = false;

    cout << "Starting Board:\n";
    printBoard(start.board, start.size);

    bool result = solve(start, goal);

    if (!result)
        cout << "\nNo solution found.\n";

    return 0;
}
