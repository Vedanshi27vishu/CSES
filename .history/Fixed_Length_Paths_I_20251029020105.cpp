#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;

// DFS returns a map: depth -> count of nodes at that depth in THIS subtree
// Also updates the final answer while merging children maps
unordered_map<int, long long> dfs(int node, int parent, int k, long long &ans) {
    unordered_map<int, long long> depthCount;
    depthCount[0] = 1; // Current node is depth 0 from itself

    for (int child : adj[node]) {
        if (child == parent) continue;

        // Get depth map from child subtree
        unordered_map<int, long long> childMap = dfs(child, node, k, ans);

        // Count valid pairs (d + d2 = k)
        for (auto &p : childMap) {
            int depthChild = p.first;
            long long countChild = p.second;

            int required = k - depthChild;
            if (depthCount.count(required)) {
                ans += countChild * depthCount[required];
            }
        }

        // Small-to-Large Trick → merge smaller map into larger
        if (childMap.size() > depthCount.size())
            swap(childMap, depthCount);

        // Increase depth by 1 for child nodes
        for (auto &p : childMap) {
            depthCount[p.first + 1] += p.second;
        }
    }

    return depthCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    adj.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    long long ans = 0;
    dfs(1, -1, k, ans);

    cout << ans << "\n";
    return 0;
}
