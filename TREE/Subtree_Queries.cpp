#include <bits/stdc++.h> // include all standard C++ libraries
using namespace std;

struct Fenwick {
    int n; // stores size of Fenwick Tree
    vector<long long> bit; // Fenwick Tree internal array

    // Constructor: initialize size and set all values to 0
    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    // Update function: add 'val' to index 'i'
    void update(int i, long long val) {
        // Move through Fenwick Tree using lowest set bit
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    // Returns sum from 1 to i
    long long sum(int i) {
        long long s = 0; // store cumulative sum
        // Move backward through Fenwick Tree using lowest set bit
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    // Returns range sum from l to r
    long long rangeSum(int l, int r) {
        return sum(r) - sum(l - 1); // prefix trick
    }
};

int n, q; // number of nodes and queries
vector<long long> val; // stores node values
vector<vector<int>> tree; // adjacency list for tree edges
vector<int> tin, tout; // store entry and exit time of each node
vector<int> euler; // flattened array after DFS
int timer = 0; // time counter for DFS

// DFS function to perform Euler tour
void dfs(int node, int parent) {
    tin[node] = ++timer; // assign entry time (increment timer first)
    euler[timer] = val[node]; // store current node's value at its time index

    // explore all children of the current node
    for (int child : tree[node]) {
        if (child != parent) // avoid going back to parent
            dfs(child, node);
    }

    tout[node] = timer; // subtree ends at the last visited time
}

int main() {
    ios::sync_with_stdio(false); // fast I/O optimization
    cin.tie(nullptr); // untie cin and cout for speed

    cin >> n >> q; // read n and q

    val.assign(n + 1, 0); // allocate value array (1-indexed)
    for (int i = 1; i <= n; i++)
        cin >> val[i]; // read each node's initial value

    tree.assign(n + 1, {}); // allocate adjacency list
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b; // read edge endpoints
        tree[a].push_back(b); // bidirectional connection
        tree[b].push_back(a);
    }

    tin.resize(n + 1); // resize entry time array
    tout.resize(n + 1); // resize exit time array
    euler.resize(n + 1); // resize flattened tree array

    dfs(1, 0); // start DFS from root (node 1)

    Fenwick fenw(n); // initialize Fenwick tree with size n

    // Build Fenwick tree using initial flattened values
    for (int i = 1; i <= n; i++)
        fenw.update(i, euler[i]);

    // Process q queries
    while (q--) {
        int type;
        cin >> type; // read query type

        if (type == 1) { // update node value
            int s;
            long long x;
            cin >> s >> x; // node s and new value x

            long long diff = x - val[s]; // difference to apply
            val[s] = x; // update stored value of node

            fenw.update(tin[s], diff); // update Fenwick tree only at entry position
        }
        else { // type == 2: subtree sum query
            int s;
            cin >> s; // read the node

            // Query range: whole subtree converted into array segment using Euler Tour
            cout << fenw.rangeSum(tin[s], tout[s]) << "\n";
        }
    }

    return 0; // program ends successfully
}
