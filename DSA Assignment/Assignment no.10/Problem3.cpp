#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int dest;
    int weight;
};

class GraphPrim {
private:
    vector<vector<Edge>> adjList;
    int vertices;

public:
    GraphPrim(int v) {
        vertices = v;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v, int w) {
        Edge e1 = {v, w};
        Edge e2 = {u, w};
        adjList[u].push_back(e1);
        adjList[v].push_back(e2);
    }

    void primMST() {
        vector<int> key(vertices, INT_MAX);
        vector<bool> inMST(vertices, false);
        vector<int> parent(vertices, -1);
        
        key[0] = 0;
        
        for (int count = 0; count < vertices - 1; count++) {
            int minKey = INT_MAX;
            int minIndex = -1;
            
            for (int v = 0; v < vertices; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }
            
            if (minIndex == -1) break;
            
            inMST[minIndex] = true;
            
            for (auto edge : adjList[minIndex]) {
                int v = edge.dest;
                int weight = edge.weight;
                
                if (!inMST[v] && weight < key[v]) {
                    parent[v] = minIndex;
                    key[v] = weight;
                }
            }
        }
        
        cout << "Minimum Spanning Tree (Prim's):\n";
        int totalWeight = 0;
        for (int i = 1; i < vertices; i++) {
            cout << parent[i] << " - " << i << " : " << key[i] << endl;
            totalWeight += key[i];
        }
        cout << "Total weight: " << totalWeight << endl;
    }

    void displayGraph() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (auto edge : adjList[i]) {
                cout << "(" << edge.dest << "," << edge.weight << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    int vertices, edges, u, v, w;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    GraphPrim graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    
    graph.displayGraph();
    graph.primMST();
    
    return 0;
}