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
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        distance[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            for (auto neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if (!visited[v] && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    pq.push({distance[v], v});
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
    
    GraphDijkstra graph(vertices);
    
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