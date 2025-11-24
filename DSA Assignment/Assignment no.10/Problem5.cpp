#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Node {
    int vertex;
    int distance;
};

class GraphDijkstra {
private:
    vector<vector<pair<int, int>>> adjList;
    int vertices;

public:
    GraphDijkstra(int v) {
        vertices = v;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
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
            
            for (auto neighbor : adjList[minIndex]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if (!visited[v] && distance[minIndex] != INT_MAX && 
                    distance[minIndex] + weight < distance[v]) {
                    distance[v] = distance[minIndex] + weight;
                }
            }
        }
        
        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < vertices; i++) {
            if (distance[i] == INT_MAX) {
                cout << "Vertex " << i << ": Unreachable" << endl;
            } else {
                cout << "Vertex " << i << ": " << distance[i] << endl;
            }
        }
    }

    void dijkstraWithPath(int start, int end) {
        vector<int> distance(vertices, INT_MAX);
        vector<bool> visited(vertices, false);
        vector<int> parent(vertices, -1);
        
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
            
            for (auto neighbor : adjList[minIndex]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if (!visited[v] && distance[minIndex] != INT_MAX && 
                    distance[minIndex] + weight < distance[v]) {
                    distance[v] = distance[minIndex] + weight;
                    parent[v] = minIndex;
                }
            }
        }
        
        if (distance[end] == INT_MAX) {
            cout << "No path exists from " << start << " to " << end << endl;
        } else {
            cout << "Shortest distance from " << start << " to " << end << ": " << distance[end] << endl;
            cout << "Path: ";
            vector<int> path;
            for (int v = end; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            for (int i = path.size() - 1; i >= 0; i--) {
                cout << path[i];
                if (i > 0) cout << " -> ";
            }
            cout << endl;
        }
    }

    void displayGraph() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (auto neighbor : adjList[i]) {
                cout << "(" << neighbor.first << "," << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    int vertices, edges, u, v, w;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    GraphDijkstra graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    
    graph.displayGraph();
    
    int start;
    cout << "Enter starting vertex for Dijkstra: ";
    cin >> start;
    
    graph.dijkstra(start);
    
    int end;
    cout << "Enter destination vertex for path finding: ";
    cin >> end;
    
    graph.dijkstraWithPath(start, end);
    
    return 0;
}