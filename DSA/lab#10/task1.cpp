#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjList;
    bool isDirected;

public:
    Graph(int vertices, bool directed) {
        numVertices = vertices;
        isDirected = directed;
        
        // Initializing adjacency matrix 
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
        
        adjList.resize(numVertices);
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        
        // Add to adjacency list
        adjList[u].push_back(v);
        
        // If undirected then reverse edge is added
        if (!isDirected) {
            adjMatrix[v][u] = 1;
            adjList[v].push_back(u);
        }
    }

    void printAdjList() {
        cout << "\nAdjacency List Representation:\n";
        for (int i = 0; i < numVertices; i++) {
            cout << i << " -> ";
            for (int j = 0; j < adjList[i].size(); j++) {
                cout << adjList[i][j];
                if (j < adjList[i].size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }

    void printAdjMatrix() {
        cout << "\nAdjacency Matrix Representation:\n";
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    int graphType;
    cout << "Is the graph directed (1) or undirected (0)? ";
    cin >> graphType;
    bool isDirected = (graphType == 1);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return 1;
    }

    string line;
    int numVertices = 0;

    while (getline(file, line)) {
        if (line.find("#vertices") != string::npos) {
            getline(file, line);
            numVertices = stoi(line);
            break;
        }
    }

    if (numVertices == 0) {
        cout << "Error: Invalid number of vertices!" << endl;
        return 1;
    }

    // graph is initialized here on basis of number of vertices and type
    Graph G(numVertices, isDirected);

    while (getline(file, line)) {
        if (line.find("#edges") != string::npos) {
            break;
        }
    }

    while (getline(file, line)) {
        // trmming spaces to avoid unnecessary spaces
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        
        if (line.empty()) continue;

        //obtaining u n=d v from (u,v)
        size_t start = line.find('(');
        size_t comma = line.find(',');
        size_t end = line.find(')');

        if (start != string::npos && comma != string::npos && end != string::npos) {
            int u = stoi(line.substr(start + 1, comma - start - 1));
            int v = stoi(line.substr(comma + 1, end - comma - 1));
            G.addEdge(u, v);
        }
    }

    file.close();

    // Print the graph
    cout << "\nGraph loaded successfully!\n";
    G.printAdjList();
    G.printAdjMatrix();

    return 0;
}