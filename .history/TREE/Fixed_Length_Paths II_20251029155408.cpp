#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> g[MAXN];
int sz[MAXN], vis[MAXN];
int n, k1, k2;
long long ans = 0;

// Fenwick Tree (BIT) for range sum queries
struct BIT {
    vector<int> bit;
    int N;
    BIT(int n) : N(n) {
        bit.assign(n + 1, 0);
    }
    void reset() {
        fill(bit.begin(), bit.end(), 0);
    }
    void update(int idx, int val) {
        idx++;
        while (idx <= N) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }
    int query(int idx) {
        if (idx < 0) return 0;
        idx++;
        int s = 0;
        while (idx > 0) {
            s += bit[idx];
            idx -= idx & -idx;
        }
        return s;
    }
    int rangeQuery(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

BIT bit(MAXN);


// Find subtree sizes
int dfs_size(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (!vis[v] && v != p) {
            sz[u] += dfs_size(v, u);
        }
    }
    return sz[u];
}

// Find centroid
int get_centroid(int u, int p, int total) {
    for (int v : g[u]) {
        if (!vis[v] && v != p && sz[v] > total / 2) {
            return get_centroid(v, u, total);
        }
    }
    return u;
}

// Collect depth info
void get_depths(int u, int p, int d, vector<int> &depths) {
    if (d > k2) return;
    depths.push_back(d);
    for (int v : g[u]) {
        if (!vis[v] && v != p) {
            get_depths(v, u, d + 1, depths);
        }
    }
}

// Solve for centroid
void solve_centroid(int cen) {
    vis[cen] = 1;
    bit.reset();
    bit.update(0, 1); // depth 0 from centroid itself

    for (int v : g[cen]) {
        if (!vis[v]) {
            vector<int> depths;
            get_depths(v, cen, 1, depths);

            for (int d : depths) {
                ans += bit.rangeQuery(k1 - d, k2 - d);
            }
            for (int d : depths) {
                bit.update(d, 1);
            }
        }
    }

    for (int v : g[cen]) {
        if (!vis[v]) {
            int total = dfs_size(v, cen);
            int cent = get_centroid(v, cen, total);
            solve_centroid(cent);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k1 >> k2;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int total = dfs_size(1, 0);
    int cen = get_centroid(1, 0, total);
    solve_centroid(cen);

    cout << ans << "\n";
    return 0;
}
