// Lab 11 – Travelling Salesman Problem (Dynamic Programming / Held-Karp)
// Description: Find the minimum-cost tour that visits every city exactly once
//              and returns to the starting city, using bitmask DP.
//              Time: O(2^n * n^2), Space: O(2^n * n). Feasible for n <= 20.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = INT_MAX / 2;

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter distance matrix (" << n << "x" << n << "), use 0 for no direct edge:\n";
    for (auto& row : dist) for (int& x : row) cin >> x;

    // Replace 0 off-diagonal with INF
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && dist[i][j] == 0) dist[i][j] = INF;

    int FULL = (1 << n) - 1;
    // dp[mask][i] = min cost to reach city i visiting exactly the cities in mask
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));

    dp[1][0] = 0; // start at city 0

    for (int mask = 1; mask <= FULL; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            if (dp[mask][u] == INF) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                if (dist[u][v] == INF) continue;
                int newMask = mask | (1 << v);
                int newCost = dp[mask][u] + dist[u][v];
                if (newCost < dp[newMask][v]) {
                    dp[newMask][v] = newCost;
                    parent[newMask][v] = u;
                }
            }
        }
    }

    // Find minimum cost to return to city 0
    int minCost = INF, lastCity = -1;
    for (int u = 1; u < n; u++) {
        if (dp[FULL][u] == INF || dist[u][0] == INF) continue;
        int cost = dp[FULL][u] + dist[u][0];
        if (cost < minCost) { minCost = cost; lastCity = u; }
    }

    if (minCost == INF) {
        cout << "No Hamiltonian cycle exists.\n";
        return 0;
    }

    // Reconstruct path
    vector<int> path;
    int mask = FULL, cur = lastCity;
    while (cur != -1) {
        path.push_back(cur);
        int prev = parent[mask][cur];
        mask ^= (1 << cur);
        cur = prev;
    }
    path.push_back(0);
    reverse(path.begin(), path.end());

    cout << "Optimal tour cost: " << minCost << "\n";
    cout << "Tour path: ";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i];
        if (i + 1 < (int)path.size()) cout << " -> ";
    }
    cout << " -> 0\n";
    return 0;
}
