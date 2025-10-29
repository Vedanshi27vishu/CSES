#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> g(n + 1);
    for (int v = 2; v <= n; ++v) {
        int p; 
        cin >> p;
        g[p].push_back(v);           // p is the boss of v
    }

    // Iterative DFS to obtain a postorder
    vector<int> order;
    order.reserve(n);
    stack<int> st;
    st.push(1);
    while (!st.empty()) {
        int v = st.top(); st.pop();
        order.push_back(v);
        for (int u : g[v]) st.push(u);
    }
    // Postorder = reverse of the above visitation for a rooted tree
    reverse(order.begin(), order.end());

    // Subtree sizes
    vector<int> sz(n + 1, 1);
    for (int v : order) {
        for (int u : g[v]) sz[v] += sz[u];
    }

    // Subordinates = subtree size - 1
    for (int v = 1; v <= n; ++v) {
        cout << (sz[v] - 1) << (v == n ? '\n' : ' ');
    }
    return 0;
}
