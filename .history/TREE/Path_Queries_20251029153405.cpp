#include <bits/stdc++.h>
using namespace std;

const int N = 200005;          // maximum number of nodes
const long long MOD = 1e9+7;   // modulo not needed here but good habit
vector<int> adj[N];            // adjacency list for the tree
long long fenwick[N];          // Fenwick Tree array for values
long long val[N];              // current value of each node

int parent[20][N];             // Binary lifting table: 2^k-th parent of node
int depth[N];                  // depth of each node from the root

// -------- Fenwick Tree Functions --------

// Add value x at position i in Fenwick Tree
void updateFenwick(int i, long long x) {
    for(; i < N; i += i & -i)
        fenwick[i] += x; // add x in that index and all relevant Fenwick buckets
}

// Query prefix sum up to index i
long long queryFenwick(int i) {
    long long s = 0;
    for(; i > 0; i -= i & -i)
        s += fenwick[i]; // accumulate all contributing BIT segments
    return s;
}

// -------- DFS to initialize parent + depth + Fenwick indexing --------

int tin[N];    // tin[node] gives Fenwick Tree index
int timer = 1; // Fenwick indexes should start from 1

void dfs(int u, int p) {
    parent[0][u] = p;     // 2^0-th parent is direct parent
    depth[u] = depth[p] + 1; // depth relative to its parent

    tin[u] = timer++;    // assign Fenwick index in DFS discovery order

    // Insert current node's value into Fenwick Tree
    updateFenwick(tin[u], val[u]);

    // Visit children
    for(int v: adj[u])
        if(v != p)
            dfs(v, u);
}

// -------- Binary Lifting Sum from root → node --------

// Computes sum of values from node u up to root
long long pathSum(int u) {
    long long res = 0;
    
    // Add current node's value
    res += queryFenwick(tin[u]) - queryFenwick(tin[u]-1);

    // Move upward using binary lifting
    for(int i = 19; i >= 0; i--) {
        int p = parent[i][u]; // find 2^i parent
        if(p > 0) {
            // Add parent value
            res += queryFenwick(tin[p]) - queryFenwick(tin[p]-1);
            u = p; // move to that parent
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;                 // number of nodes and queries

    for(int i = 1; i <= n; i++)
        cin >> val[i];             // initial values of nodes

    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;             // read edges
        adj[a].push_back(b);       // build tree bidirectionally
        adj[b].push_back(a);
    }

    dfs(1, 0);                     // root DFS from node 1

    // Build binary lifting table
    for(int i = 1; i < 20; i++)
        for(int v = 1; v <= n; v++)
            parent[i][v] = parent[i-1][parent[i-1][v]];

    // Process queries
    while(q--) {
        int type;
        cin >> type;

        if(type == 1) {
            // Update query: change value of node s to x
            int s; long long x;
            cin >> s >> x;

            long long diff = x - val[s];  // find difference
            val[s] = x;                    // update stored value
            updateFenwick(tin[s], diff);   // update BIT
        }
        else {
            // Query: path sum from root to node s
            int s;
            cin >> s;
            cout << pathSum(s) << "\n";  // print required sum
        }
    }
    return 0;
}
