#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> dist;
int farthestNode;

void dfs(int node, int parent, int d) {
    dist[node] = d;
    if (dist[node] > dist[farthestNode]) {
        farthestNode = node;
    }
    for (int next : adj[node]) {
        if (next != parent) {
            dfs(next, node, d + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Step 1: DFS from node 1 to find A
    dist.assign(n + 1, -1);
    farthestNode = 1;
    dfs(1, -1, 0);
    int A = farthestNode;

    // Step 2: DFS from A to find B + distA
    dist.assign(n + 1, -1);
    farthestNode = A;
    dfs(A, -1, 0);
    vector<int> distA = dist;
    int B = farthestNode;

    // Step 3: DFS from B to get distB
    dist.assign(n + 1, -1);
    dfs(B, -1, 0);
    vector<int> distB = dist;

    // Final output
    for(int i = 1; i <= n; i++) {
        cout << max(distA[i], distB[i]) << " ";
    }

    return 0;
}
