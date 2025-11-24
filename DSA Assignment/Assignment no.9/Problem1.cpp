#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class GraphMatrix {
private:
    int** adjMatrix;
    int vertices;
    bool* visited;

public:
    GraphMatrix(int v) {
        vertices = v;
        adjMatrix = new int*[vertices];
        visited = new bool[vertices];
        
        for (int i = 0; i < vertices; i++) {
            adjMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void BFS(int start) {
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        queue<int> q;
        visited[start] = true;
        q.push(start);
        
        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";
            
            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        stack<int> s;
        s.push(start);
        
        cout << "DFS Traversal: ";
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            
            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
                
                for (int i = vertices - 1; i >= 0; i--) {
                    if (adjMatrix[current][i] == 1 && !visited[i]) {
                        s.push(i);
                    }
                }
            }
        }
        cout << endl;
    }

    void displayMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int vertices, edges, u, v;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    GraphMatrix graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v;
        graph.addEdge(u, v);
    }
    
    graph.displayMatrix();
    
    int start;
    cout << "Enter starting vertex for traversals: ";
    cin >> start;
    
    graph.BFS(start);
    graph.DFS(start);
    
    return 0;
}