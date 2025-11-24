#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class GraphList {
private:
    vector<vector<int>> adjList;
    int vertices;
    vector<bool> visited;

public:
    GraphList(int v) {
        vertices = v;
        adjList.resize(vertices);
        visited.resize(vertices, false);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void BFS(int start) {
        fill(visited.begin(), visited.end(), false);
        
        queue<int> q;
        visited[start] = true;
        q.push(start);
        
        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";
            
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        fill(visited.begin(), visited.end(), false);
        
        stack<int> s;
        s.push(start);
        
        cout << "DFS Traversal: ";
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            
            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
                
                for (int i = adjList[current].size() - 1; i >= 0; i--) {
                    int neighbor = adjList[current][i];
                    if (!visited[neighbor]) {
                        s.push(neighbor);
                    }
                }
            }
        }
        cout << endl;
    }

    void displayList() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int vertices, edges, u, v;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    GraphList graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v;
        graph.addEdge(u, v);
    }
    
    graph.displayList();
    
    int start;
    cout << "Enter starting vertex for traversals: ";
    cin >> start;
    
    graph.BFS(start);
    graph.DFS(start);
    
    return 0;
}