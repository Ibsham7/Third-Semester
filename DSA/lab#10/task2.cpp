#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
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

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
    }

    void shortestPath(int start, int end) {
        vector<bool> visited(vertices, false);
        vector<int> parent(vertices, -1);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        bool found = false;

        while (!q.empty() && !found) {
            int current = q.front();
            q.pop();

            if (current == end) {
                found = true;
                break;
            }

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        if (!found) {
            cout << "No path exists between the given vertices." << endl;
            return;
        }

        vector<int> path;
        int vertex = end;
        while (vertex != -1) {
            path.push_back(vertex);
            vertex = parent[vertex];
        }

        reverse(path.begin(), path.end());

        cout << "Shortest path from " << start << " to " << end << ":" << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
};

int main() {
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (source destination):" << endl;
    for (int i = 0; i < edges; i++) {
        int src, dest;
        cin >> src >> dest;
        g.addEdge(src, dest);
    }

    int start, end;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter end vertex: ";
    cin >> end;

    g.shortestPath(start, end);

    return 0;
}