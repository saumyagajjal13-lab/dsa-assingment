#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

class GraphKruskalMatrix {
private:
    int** adjMatrix;
    int vertices;
    vector<int> parent, rank;

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

public:
    GraphKruskalMatrix(int v) {
        vertices = v;
        adjMatrix = new int*[vertices];
        parent.resize(vertices);
        rank.resize(vertices, 0);
        
        for (int i = 0; i < vertices; i++) {
            adjMatrix[i] = new int[vertices];
            parent[i] = i;
            for (int j = 0; j < vertices; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
    }

    void kruskalMST() {
        vector<Edge> edges;
        
        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (adjMatrix[i][j] != 0) {
                    edges.push_back({i, j, adjMatrix[i][j]});
                }
            }
        }
        
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });
        
        vector<Edge> mst;
        int totalWeight = 0;
        
        for (auto edge : edges) {
            if (find(edge.u) != find(edge.v)) {
                mst.push_back(edge);
                totalWeight += edge.weight;
                unionSets(edge.u, edge.v);
            }
        }
        
        cout << "Minimum Spanning Tree (Kruskal's):\n";
        for (auto edge : mst) {
            cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        }
        cout << "Total weight: " << totalWeight << endl;
    }
};

int main() {
    int vertices, edges, u, v, w;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    GraphKruskalMatrix graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    
    graph.kruskalMST();
    
    return 0;
}