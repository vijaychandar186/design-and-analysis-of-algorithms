// Lab 08 – Kruskal's Minimum Spanning Tree
// Description: Find the MST of a weighted undirected graph using Kruskal's
//              greedy algorithm with Union-Find (path compression + rank).
//              Time complexity: O(E log E).

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge { int u, v, weight; };

struct UnionFind {
    vector<int> parent, rank_;
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v weight):\n";
    for (auto& e : edges) cin >> e.u >> e.v >> e.weight;

    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

    UnionFind uf(V);
    vector<Edge> mst;
    int totalWeight = 0;

    for (const auto& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.weight;
        }
    }

    cout << "\nMinimum Spanning Tree edges:\n";
    for (const auto& e : mst)
        cout << "  " << e.u << " -- " << e.v << "  (weight=" << e.weight << ")\n";
    cout << "Total MST weight: " << totalWeight << "\n";
    return 0;
}
