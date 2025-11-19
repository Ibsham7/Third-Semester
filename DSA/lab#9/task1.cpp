#include <iostream>
#include <vector>
#include <list>
#include <iomanip>    
#include <algorithm>  

using namespace std;

class Graph {
private:
    vector<vector<int>> adjMatrix; // the grid
    vector<list<int>> adjList;     // the lists
    int numNodes;

public:
    Graph(int initialNodes = 0) : numNodes(initialNodes) {
        adjMatrix.resize(numNodes, vector<int>(numNodes, 0));
        adjList.resize(numNodes);
    }

    void addNode() {
        int oldNumNodes = numNodes;
        numNodes++;

        // update grid
        adjMatrix.push_back(vector<int>(numNodes, 0));
        for (int i = 0; i < oldNumNodes; ++i) {
            adjMatrix[i].push_back(0);
        }

        // update lists
        adjList.push_back(list<int>());
    }

    void addEdge(int u, int v) {
        if (u < 0 || u >= numNodes || v < 0 || v >= numNodes) {
            cout << "Error: Bad node index." << endl;
            return;
        }
        
        // matrix part
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // list part... gotta keep it sorted
        auto sortedInsert = [](list<int>& l, int val) {
            auto it = l.begin();
            while (it != l.end() && *it < val) {
                ++it;
            }
            if (it == l.end() || *it != val) {
                l.insert(it, val);
            }
        };

        sortedInsert(adjList[u], v);
        sortedInsert(adjList[v], u);
    }

    void deleteEdge(int u, int v) {
        if (u < 0 || u >= numNodes || v < 0 || v >= numNodes) {
            cout << "Error: Bad node index." << endl;
            return;
        }

        // matrix part
        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;

        // list part
        adjList[u].remove(v);
        adjList[v].remove(u);
    }

    void deleteNode(int node) {
        if (node < 0 || node >= numNodes) {
            cout << "Error: Bad node index." << endl;
            return;
        }


        // remove row
        adjMatrix.erase(adjMatrix.begin() + node);

        // remove col
        for (int i = 0; i < numNodes - 1; ++i) {
            adjMatrix[i].erase(adjMatrix[i].begin() + node);
        }


        // remove this node's list
        adjList.erase(adjList.begin() + node);

        // fix everyone else's list
        for (int i = 0; i < numNodes - 1; ++i) {
            adjList[i].remove(node); // remove links to dead node

        
            for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                if (*it > node) {
                    *it = *it - 1; 
                }
            }
        }
        
        numNodes--;
    }

    void printGraph() {
        cout << "Adjacency Matrix:" << endl;
        cout << "   ";
        for (int i = 0; i < numNodes; ++i) {
            cout << setw(2) << i;
        }
        cout << endl << "   ";
        for (int i = 0; i < numNodes; ++i) {
            cout << "--";
        }
        cout << endl;

        for (int i = 0; i < numNodes; ++i) {
            cout << setw(2) << i << "|";
            for (int j = 0; j < numNodes; ++j) {
                cout << setw(2) << adjMatrix[i][j];
            }
            cout << endl;
        }

        cout << "\nSorted Adjacency List:" << endl;
        for (int i = 0; i < numNodes; ++i) {
            cout << i << ": ";
            bool first = true;
            for (int neighbor : adjList[i]) {
                if (!first) {
                    cout << ", ";
                }
                cout << neighbor;
                first = false;
            }
            cout << endl;
        }
    }
};


int main() {
    cout << "Creating graph with 3 nodes (0, 1, 2)..." << endl;
    Graph g(3);

    cout << "Adding edges (0,1), (0,2), (1,2)..." << endl;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);

    cout << "\nGraph after adding edges:" << endl;
    g.printGraph();

    cout << "\n------------------------------------" << endl;
    cout << "\nAfter deleting edge (0, 1):" << endl;
    g.deleteEdge(0, 1);
    g.printGraph();

    cout << "\n------------------------------------" << endl;
    cout << "\nAfter adding a new node (Node 3):" << endl;
    g.addNode();
    cout << "Adding edge (3, 0):" << endl;
    g.addEdge(3, 0);
    g.printGraph();
    
    cout << "\n------------------------------------" << endl;
    cout << "\nAfter adding another new node (Node 4):" << endl;
    g.addNode();
    cout << "Adding edge (4, 2):" << endl;
    g.addEdge(4, 2);
    g.printGraph();

    cout << "\n------------------------------------" << endl;
    cout << "\nAfter deleting node 1:" << endl;
    cout << "(Note: Node 2->1, Node 3->2, Node 4->3)" << endl;
    g.deleteNode(1);
    g.printGraph();

    return 0;
}