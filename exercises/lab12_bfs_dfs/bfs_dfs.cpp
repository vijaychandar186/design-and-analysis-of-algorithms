// Lab 12 – BFS and DFS Implementation with Array (Adjacency Matrix)
// Description: Implement Breadth-First Search and Depth-First Search on
//              an undirected graph represented as an adjacency matrix.
//              BFS uses a queue; DFS uses a stack (iterative).
//              Time: O(V^2) for adjacency matrix representation.

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int V;
vector<vector<int>> adj; // adjacency matrix

void bfs(int start) {
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS from vertex " << start << ": ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v = 0; v < V; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
}

void dfs(int start) {
    vector<bool> visited(V, false);
    stack<int> s;
    s.push(start);

    cout << "DFS from vertex " << start << ": ";
    while (!s.empty()) {
        int u = s.top(); s.pop();
        if (visited[u]) continue;
        visited[u] = true;
        cout << u << " ";
        // Push neighbours in reverse order for natural left-to-right traversal
        for (int v = V - 1; v >= 0; v--) {
            if (adj[u][v] && !visited[v])
                s.push(v);
        }
    }
    cout << "\n";
}

int main() {
    int E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    adj.assign(V, vector<int>(V, 0));
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v; cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    bfs(start);
    dfs(start);
    return 0;
}
