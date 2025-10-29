#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
long long seg[4*N];          // segment tree
long long val[N];            // value of each node
vector<int> adj[N];          // tree adjacency list

int parent[N], depth[N];     // parent and depth for each node
int heavy[N], head[N], pos[N], sz[N];
int cur_pos = 1;

// ---------- Segment Tree Functions ----------

// Build segment tree using current base values
void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx] = val[pos[l]]; // place node's value in segment tree position
        return;
    }
    int mid = (l+r)/2;
    build(2*idx, l, mid);
    build(2*idx+1, mid+1, r);
    seg[idx] = seg[2*idx] + seg[2*idx+1];
}

// Point update (change value at position p)
void update(int idx, int l, int r, int p, long long x) {
    if(l == r) {
        seg[idx] = x;
        return;
    }
    int mid = (l+r)/2;
    if(p <= mid) update(2*idx, l, mid, p, x);
    else update(2*idx+1, mid+1, r, p, x);
    seg[idx] = seg[2*idx] + seg[2*idx+1];
}

// Range sum query on segment tree
long long query(int idx, int l, int r, int ql, int qr) {
    if(qr < l || r < ql) return 0;
    if(ql <= l && r <= qr) return seg[idx];
    int mid = (l+r)/2;
    return query(2*idx, l, mid, ql, qr) +
           query(2*idx+1, mid+1, r, ql, qr);
}

// ---------- Heavy Light Decomposition Steps ----------

// DFS1: compute subtree sizes + heavy child
void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    sz[u] = 1;
    heavy[u] = -1;

    for(int v : adj[u]) if(v != p) {
        dfs1(v, u);
        sz[u] += sz[v];
        if(heavy[u] == -1 || sz[v] > sz[heavy[u]])
            heavy[u] = v;     // heavy child → maximum subtree
    }
}

// DFS2: assign head of chain + position in segment tree base array
void dfs2(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;

    if(heavy[u] != -1)
        dfs2(heavy[u], h);   // continue same chain

    for(int v : adj[u])
        if(v != parent[u] && v != heavy[u])
            dfs2(v, v);      // start a new chain
}

// Query root → u using HLD
long long queryPath(int u) {
    long long res = 0;
    while(head[u] != 1) {  // until reach root chain
        res += query(1, 1, N, pos[head[u]], pos[u]);
        u = parent[head[u]];
    }
    res += query(1, 1, N, pos[1], pos[u]); // last segment including root
    return res;
}

// ---------- MAIN ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++)
        cin >> val[i];

    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1, 0);         // compute heavy children
    dfs2(1, 1);         // decompose into chains

    // reorder values by position for segment tree
    for(int i = 1; i <= n; i++)
        val[pos[i]] = val[i];

    build(1, 1, N);     // build segment tree

    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int s; long long x;
            cin >> s >> x;
            update(1, 1, N, pos[s], x); // single node update
        }
        else {
            int s;
            cin >> s;
            cout << queryPath(s) << "\n"; // path sum root→s
        }
    }
    return 0;
}
