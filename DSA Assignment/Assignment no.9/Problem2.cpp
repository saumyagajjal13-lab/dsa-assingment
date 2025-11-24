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
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        key[0] = 0;
        pq.push({0, 0});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            inMST[u] = true;
            
            for (auto edge : adjList[u]) {
                int v = edge.dest;
                int weight = edge.weight;
                
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v});
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
    
    graph.primMST();
    
    return 0;
}