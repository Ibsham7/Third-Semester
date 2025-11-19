#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int v) {
        vertices = v;
        adjList.resize(v);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For undirected graph
    }

    bool isConnected() {
        if (vertices == 0) return true;

        vector<bool> visited(vertices, false);
        queue<int> q;
        
        // Start BFS from vertex 0
        q.push(0);
        visited[0] = true;
        int reachableCount = 1;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    reachableCount++;
                }
            }
        }

        return reachableCount == vertices;
    }

    void display() {
        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int vertices, edges;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    Graph g(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    
    if (g.isConnected()) {
        cout << "Graph is connected." << endl;
    } else {
        cout << "Graph is disconnected." << endl;
    }
    
    return 0;
}