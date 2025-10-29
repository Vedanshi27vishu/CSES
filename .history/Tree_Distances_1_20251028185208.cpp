#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, int d, vector<int> &dist, vector<vector<int>> &adj, int &farthestNode) {
    dist[node] = d;
   //Check if the current node has greater distance

If yes → update farthestNode to this node
    if (dist[node] > dist[farthestNode]) {
        farthestNode = node;
    }

    for (int next : adj[node]) {
        if (next != parent) {
            dfs(next, node, d + 1, dist, adj, farthestNode);
        }
    }
}

int main() {

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Step 1: DFS from 1 to find A
    vector<int> distA(n + 1, -1);
    int A = 1;
    dfs(1, -1, 0, distA, adj, A);

    // Step 2: DFS from A to find B & fill distA
    fill(distA.begin(), distA.end(), -1);
    int B = A;
    dfs(A, -1, 0, distA, adj, B);

    // Step 3: DFS from B to fill distB
    vector<int> distB(n + 1, -1);
    dfs(B, -1, 0, distB, adj, B);

    // Step 4: Answer for each node
    for (int i = 1; i <= n; i++) {
        cout << max(distA[i], distB[i]) << " ";
    }

    return 0;
}
