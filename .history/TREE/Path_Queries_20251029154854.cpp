#include <bits/stdc++.h>
using namespace std;

// ---- GLOBAL CONSTANTS ----
const int MAXN = 200005; // Maximum nodes

// ---- DATA STRUCTURES ----
vector<int> graphAdj[MAXN]; // Adjacency list for the tree
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN], subtreeSize[MAXN];
int value[MAXN]; // Value of each node
int curPos; // Position index for base array of HLD

// Segment Tree for max
int seg[4 * MAXN];

// ---- SEGMENT TREE FUNCTIONS ----

// Build segment tree
void build(int idx, int l, int r) {
    if (l == r) {
        seg[idx] = value[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx * 2, l, mid);
    build(idx * 2 + 1, mid + 1, r);
    seg[idx] = max(seg[idx * 2], seg[idx * 2 + 1]);
}

// Update value at position p
void updateSeg(int idx, int l, int r, int p, int val) {
    if (l == r) {
        seg[idx] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid) updateSeg(idx * 2, l, mid, p, val);
    else updateSeg(idx * 2 + 1, mid + 1, r, p, val);
    seg[idx] = max(seg[idx * 2], seg[idx * 2 + 1]);
}

// Query max in segment [L, R]
int querySeg(int idx, int l, int r, int L, int R) {
    if (R < l || r < L) return INT_MIN; // No overlap
    if (L <= l && r <= R) return seg[idx]; // Full overlap
    int mid = (l + r) / 2;
    return max(querySeg(idx * 2, l, mid, L, R),
               querySeg(idx * 2 + 1, mid + 1, r, L, R));
}

// ---- HEAVY LIGHT DECOMPOSITION ----

// DFS to compute sizes & find heavy child
int dfs(int u) {
    subtreeSize[u] = 1;
    int maxSubtree = 0;
    heavy[u] = -1;

    for (int v : graphAdj[u]) {
        if (v == parent[u]) continue;
        parent[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
        subtreeSize[u] += subtreeSize[v];

        // Heavy child: the child with largest subtree
        if (subtreeSize[v] > maxSubtree) {
            maxSubtree = subtreeSize[v];
            heavy[u] = v;
        }
    }
    return subtreeSize[u];
}

// Decompose into chains
void decompose(int u, int h) {
    head[u] = h;      // Head of current chain
    pos[u] = ++curPos; // Assign position in base array

    // Continue chain if heavy child exists
    if (heavy[u] != -1)
        decompose(heavy[u], h);

    // Create new chains for light children
    for (int v : graphAdj[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        decompose(v, v);
    }
}

// Query maximum on path a -> b
int queryPath(int a, int b) {
    int res = INT_MIN;
    while (head[a] != head[b]) {
        if (depth[head[a] ] < depth[ head[b] ])
            swap(a, b);
        res = max(res, querySeg(1, 1, curPos, pos[head[a]], pos[a]));
        a = parent[head[a]];
    }
    if (depth[a] > depth[b]) swap(a, b);
    res = max(res, querySeg(1, 1, curPos, pos[a], pos[b]));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> originalVal(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> originalVal[i];

    // Read edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graphAdj[a].push_back(b);
        graphAdj[b].push_back(a);
    }

    // Build HLD
    parent[1] = 0;
    depth[1] = 0;
    dfs(1);
    curPos = 0;
    decompose(1, 1);

    // Assign values in base array
    for (int i = 1; i <= n; i++)
        value[pos[i]] = originalVal[i];

    // Build segment tree
    build(1, 1, curPos);

    // Process queries
    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Change value of node s to x
            int s, x;
            cin >> s >> x;
            updateSeg(1, 1, curPos, pos[s], x);
        }
        else {
            // Query max on path
            int a, b;
            cin >> a >> b;
            cout << queryPath(a, b) << " ";
        }
    }
    return 0;
}
