#include <bits/stdc++.h>
using namespace std;

/*
📌 dfs_size()
Goal: Count subtree size rooted at u
Used to find centroid (balance condition)
*/
int dfs_size(int u, int p, vector<vector<int>>& adj, vector<int>& subtree, vector<bool>& removed) {
    subtree[u] = 1;
    for (int v : adj[u]) {
        if (!removed[v] && v != p)
            subtree[u] += dfs_size(v, u, adj, subtree, removed);
    }
    return subtree[u];
}

/*
📌 find_centroid()
Centroid = a node such that:
-> No resulting subtree has more than total/2 nodes
*/
int find_centroid(int u, int p, int total,
                  vector<vector<int>>& adj, vector<int>& subtree, vector<bool>& removed) {

    for (int v : adj[u]) {
        if (!removed[v] && v != p && subtree[v] > total / 2)
            return find_centroid(v, u, total, adj, subtree, removed);
    }
    return u;
}

/*
📌 dfs_depth()
Collect depths from centroid into child's subtree
Stop when d > k (useless for counting)
*/
void dfs_depth(int u, int p, int d, int k,
               vector<vector<int>>& adj, vector<bool>& removed,
               vector<int>& depths) {

    if (d > k) return;
    depths.push_back(d);

    for (int v : adj[u]) {
        if (!removed[v] && v != p)
            dfs_depth(v, u, d + 1, k, adj, removed, depths);
    }
}

/*
📌 process()
Count valid pairs:
- Use map freq to store already counted depths
- For each new depth d:
  Check if depth (k-d) exists → Valid path of exactly k edges ✅
*/
void process(int centroid, int k, long long &result,
             vector<vector<int>>& adj, vector<bool>& removed) {

    unordered_map<int,int> depthFreq;
    depthFreq[0] = 1;  // centroid contributes depth=0

    for (int v : adj[centroid]) {
        if (removed[v]) continue;

        vector<int> depths;
        dfs_depth(v, centroid, 1, k, adj, removed, depths);

        // Count paths combining two subtrees through centroid
        for (int d : depths) {
            if (k - d >= 0)
                result += depthFreq[k - d];
        }

        // Insert depths from this subtree for future matches
        for (int d : depths)
            depthFreq[d]++;
    }
}

/*
📌 decompose()
Main centroid decomposition recursion:
1️⃣ Find subtree size
2️⃣ Find centroid
3️⃣ Count valid paths going through centroid
4️⃣ Remove centroid & solve smaller subtrees
*/
void decompose(int u, int k, long long &result,
               vector<vector<int>>& adj,
               vector<int>& subtree, vector<bool>& removed) {

    int total = dfs_size(u, -1, adj, subtree, removed);
    int centroid = find_centroid(u, -1, total, adj, subtree, removed);

    process(centroid, k, result, adj, removed);
    removed[centroid] = true; // Cut centroid out

    for (int v : adj[centroid]) {
        if (!removed[v])
            decompose(v, k, result, adj, subtree, removed);
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);
    vector<int> subtree(n + 1);
    vector<bool> removed(n + 1, false);
    long long result = 0;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    decompose(1, k, result, adj, subtree, removed);

    cout << result << endl;
    return 0;
}
