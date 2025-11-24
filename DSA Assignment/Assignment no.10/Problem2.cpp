#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class GraphDijkstraMatrix {
private:
    int** adjMatrix;
    int vertices;

public:
    GraphDijkstraMatrix(int v) {
        vertices = v;
        adjMatrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            adjMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
    }

    void dijkstra(int start) {
        vector<int> distance(vertices, INT_MAX);
        vector<bool> visited(vertices, false);
        
        distance[start] = 0;
        
        for (int count = 0; count < vertices - 1; count++) {
            int minDistance = INT_MAX;
            int minIndex = -1;
            
            for (int v = 0; v < vertices; v++) {
                if (!visited[v] && distance[v] <= minDistance) {
                    minDistance = distance[v];
                    minIndex = v;
                }
            }
            
            if (minIndex == -1) break;
            
            visited[minIndex] = true;
            
            for (int v = 0; v < vertices; v++) {
                if (!visited[v] && adjMatrix[minIndex][v] != 0 && 
                    distance[minIndex] != INT_MAX && 
                    distance[minIndex] + adjMatrix[minIndex][v] < distance[v]) {
                    distance[v] = distance[minIndex] + adjMatrix[minIndex][v];
                }
            }
        }
        
        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i << ": " << distance[i] << endl;
        }
    }
};

int main() {
    int vertices, edges, u, v, w;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    GraphDijkstraMatrix graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    
    int start;
    cout << "Enter starting vertex: ";
    cin >> start;
    
    graph.dijkstra(start);
    
    return 0;
}