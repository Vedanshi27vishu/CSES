#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
long long seg[4*N], nodeVal[N];
vector<int> g[N];
int parent[N], depth[N], heavy[N], head[N], pos[N], sz[N];
int timer = 0;

// 1️⃣ Segment Tree: Range Sum
void update(int idx, int l, int r, int p, long long v) {
    if(l == r) {
        seg[idx] = v;
        return;
    }
    int mid = (l+r)/2;
    if(p <= mid) update(idx*2, l, mid, p, v);
    else update(idx*2+1, mid+1, r, p, v);
    seg[idx] = seg[idx*2] + seg[idx*2+1];
}

long long query(int idx, int l, int r, int ql, int qr) {
    if(qr < l || r < ql) return 0;
    if(ql <= l && r <= qr) return seg[idx];
    int mid = (l+r)/2;
    return query(idx*2, l, mid, ql, qr) +
           query(idx*2+1, mid+1, r, ql, qr);
}

// 2️⃣ DFS1: Subtree size + Heavy child
void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    sz[u] = 1;
    heavy[u] = -1;
    for(int v : g[u]) {
        if(v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(heavy[u] == -1 || sz[v] > sz[heavy[u]])
            heavy[u] = v;
    }
}

// 3️⃣ DFS2: Decompose chains + assign position index
void dfs2(int u, int h) {
    head[u] = h;
    pos[u] = ++timer;
    if(heavy[u] != -1)
        dfs2(heavy[u], h);
    for(int v: g[u]) {
        if(v != parent[u] && v != heavy[u])
            dfs2(v, v);
    }
}

// ✅ Query root → node using HLD jumps
long long queryPath(int u) {
    long long ans = 0;
    while(head[u] != 1) { // jump to head of chain
        ans += query(1, 1, timer, pos[head[u]], pos[u]);
        u = parent[head[u]];
    }
    // final part on root's chain
    ans += query(1, 1, timer, pos[1], pos[u]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    for(int i=1; i<=n; i++) cin >> nodeVal[i];

    for(int i=0; i<n-1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // Build HLD
    dfs1(1, 0);
    dfs2(1, 1);

    // Insert initial values into segment tree based on pos[]
    for(int i=1; i<=n; i++)
        update(1, 1, n, pos[i], nodeVal[i]);

    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int s; long long x;
            cin >> s >> x;
            update(1, 1, n, pos[s], x);
        }
        else {
            int s;
            cin >> s;
            cout << queryPath(s) << "\n";
        }
    }
}
