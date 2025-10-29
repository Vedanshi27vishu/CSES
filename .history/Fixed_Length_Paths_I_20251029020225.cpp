#include <bits/stdc++.h>
using namespace std;

class Solver {
    int n, k;
    vector<vector<int>> adj;
    vector<bool> removed;
    vector<int> subtree;
    long long ans = 0;

public:
    Solver(int n, int k) : n(n), k(k), adj(n), removed(n, false), subtree(n) {}

    void addEdge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Step 1: compute subtree sizes for centroid search
    int getSize(int u, int p) {
        subtree[u] = 1;
        for (int v : adj[u])
            if (v != p && !removed[v])
                subtree[u] += getSize(v, u);
        return subtree[u];
    }

    // Step 2: find centroid of current component
    int getCentroid(int u, int p, int total) {
        for (int v : adj[u])
            if (v != p && !removed[v] && subtree[v] > total / 2)
                return getCentroid(v, u, total);
        return u;
    }

    // Collect depths of nodes in this subtree
    void collectDepths(int u, int p, int depth, vector<int> &depths) {
        if (depth > k) return;
        depths.push_back(depth);
        for (int v : adj[u])
            if (v != p && !removed[v])
                collectDepths(v, u, depth + 1, depths);
    }

    // Count valid paths passing through centroid
    void decompose(int root) {
        int total = getSize(root, -1);
        int centroid = getCentroid(root, -1, total);
        removed[centroid] = true;

        unordered_map<int, int> depthCount;
        depthCount[0] = 1; // centroid depth

        // Solve for each subtree of centroid
        for (int v : adj[centroid]) {
            if (removed[v]) continue;

            vector<int> depths;
            collectDepths(v, centroid, 1, depths);

            // Count paths where depth + d2 = k
            for (int d : depths) {
                if (depthCount.count(k - d))
                    ans += depthCount[k - d];
            }

            // Add these depths for future subtrees
            for (int d : depths)
                depthCount[d]++;
        }

        // Recurse into remaining components
        for (int v : adj[centroid])
            if (!removed[v])
                decompose(v);
    }

    long long solve() {
        decompose(0);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    Solver solver(n, k);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        solver.addEdge(a - 1, b - 1);
    }

    cout << solver.solve() << "\n";
    return 0;
}
