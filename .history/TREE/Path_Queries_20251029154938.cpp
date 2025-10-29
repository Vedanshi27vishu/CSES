#include <bits/stdc++.h> // Includes all standard library headers
using namespace std;

const int N = 200005; // Maximum number of nodes

// Segment tree and arrays for HLD
long long seg[4*N];  // Segment tree array for range sum queries
long long nodeVal[N]; // Stores original node values
vector<int> g[N];     // Adjacency list of the tree

// HLD supporting arrays
int parent[N];  // Parent of each node
int depth[N];   // Depth of each node from root
int heavy[N];   // Stores heavy child of each node
int head[N];    // Head of the heavy chain for each node
int pos[N];     // Position/index of node in the segment tree array
int sz[N];      // Subtree size of node

int timer = 0;  // Time counter for assigning pos[] values

// ✅ Segment Tree Update: Set value at position p
void update(int idx, int l, int r, int p, long long v) {
    if (l == r) {        // Leaf node: update directly
        seg[idx] = v;
        return;
    }
    int mid = (l+r) / 2; // Mid point of range
    if (p <= mid) update(idx*2, l, mid, p, v);     // Go left
    else update(idx*2+1, mid+1, r, p, v);          // Go right
    
    seg[idx] = seg[idx*2] + seg[idx*2+1]; // Recalculate parent value
}

// ✅ Segment Tree Query: returns sum in range [ql, qr]
long long query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0; // No overlap
    if (ql <= l && r <= qr) return seg[idx]; // Fully inside range
    
    int mid = (l+r) / 2;
    return query(idx*2, l, mid, ql, qr) +   // Query left child
           query(idx*2+1, mid+1, r, ql, qr); // Query right child
}

// ✅ DFS1: compute parent, depth, subtree size, and heavy child
void dfs1(int u, int p) {
    parent[u] = p;           // Store parent
    depth[u] = depth[p] + 1; // Depth = parent's depth + 1
    sz[u] = 1;               // Initially subtree size = 1
    heavy[u] = -1;           // No heavy child yet
    
    for (int v : g[u]) {     // Traverse children
        if (v == p) continue; // Avoid parent
        dfs1(v, u);          // DFS into child
        sz[u] += sz[v];      // Add child's subtree size
        
        if (heavy[u] == -1 || sz[v] > sz[heavy[u]])
            heavy[u] = v; // Heavy child = biggest subtree
    }
}

// ✅ DFS2: assign position + create heavy-light chains
void dfs2(int u, int h) {
    head[u] = h;     // Assign current chain head
    pos[u] = ++timer; // Assign new position for segment tree
    
    if (heavy[u] != -1)
        dfs2(heavy[u], h); // Continue heavy chain
    
    // For all light edges
    for (int v : g[u])
        if (v != parent[u] && v != heavy[u])
            dfs2(v, v); // Start new chain with itself as head
}

// ✅ Query sum from root to node u
long long queryPath(int u) {
    long long ans = 0;
    
    // Move from node to root chain by chain
    while (head[u] != 1) { 
        ans += query(1, 1, timer, pos[head[u]], pos[u]); // query segment tree on chain
        u = parent[head[u]]; // Jump to parent chain
    }
    
    // Final segment including root
    ans += query(1, 1, timer, pos[1], pos[u]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q; // Input number of nodes and queries

    for (int i = 1; i <= n; i++)
        cin >> nodeVal[i]; // Input node values

    // Read tree edges
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // Build Heavy-Light Decomposition
    dfs1(1, 0); // Root = 1
    dfs2(1, 1); // Head of root chain = 1

    // Initialize segment tree with node values in HLD order
    for (int i = 1; i <= n; i++)
        update(1, 1, n, pos[i], nodeVal[i]);

    // Process queries
    while (q--) {
        int type;
        cin >> type;
        
        if (type == 1) { // Update query
            int s; long long x;
            cin >> s >> x;
            update(1, 1, n, pos[s], x); // Update node s
        }
        else { // Query type 2: root → node path sum
            int s;
            cin >> s;
            cout << queryPath(s) << "\n";
        }
    }
}
