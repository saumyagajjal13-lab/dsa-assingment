#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

class GraphKruskal {
private:
    vector<Edge> edges;
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
    GraphKruskal(int v) {
        vertices = v;
        parent.resize(vertices);
        rank.resize(vertices, 0);
        for (int i = 0; i < vertices; i++) {
            parent[i] = i;
        }
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    void kruskalMST() {
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

    void displayEdges() {
        cout << "All Edges:\n";
        for (auto edge : edges) {
            cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        }
    }
};

int main() {
    int vertices, edges, u, v, w;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    GraphKruskal graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    
    graph.displayEdges();
    graph.kruskalMST();
    
    return 0;
}