#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int n, LOG;
  vector<vector<int>> adj; // adjacency list
  vector<int> depth;
  vector<vector<int>> parent; // parent[k][v] = 2^k-th parent of v

  Solution(int n)
  {
    this->n = n;
    LOG = ceil(log2(n)); // max power needed log2(n)
    adj.resize(n + 1);
    depth.resize(n + 1, 0);
    parent.assign(LOG + 1, vector<int>(n + 1, -1));
  }

  void addEdge(int a, int b)
  {
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // DFS to fill depth[] & immediate parent
  void dfs(int node, int par)
  {
    parent[0][node] = par; // 2^0 = parent itself
    for (int child : adj[node])
    {
      if (child != par)
      {
        depth[child] = depth[node] + 1;
        dfs(child, node);
      }
    }
  }

  // Preprocess parent table for binary lifting
  void build()
  {
    dfs(1, -1); // assume 1 as root

    // Fill every 2^k parent using DP
    for (int k = 1; k <= LOG; k++)
    {
      for (int v = 1; v <= n; v++)
      {
        if (parent[k - 1][v] != -1)
          parent[k][v] = parent[k - 1][parent[k - 1][v]];
      }
    }
  }

  // Lift node u upward by "jump" steps
  int lift(int u, int jump)
  {
    for (int k = 0; k <= LOG; k++)
    {
      if (jump & (1 << k))
      {
        u = parent[k][u];
        if (u == -1)
          break;
      }
    }
    return u;
  }

  // LCA in O(logN)
  int lca(int a, int b)
  {
    if (depth[a] < depth[b])
      swap(a, b);

    // 1️⃣ Bring both to same depth
    a = lift(a, depth[a] - depth[b]);

    if (a == b)
      return a;

    // 2️⃣ Lift both until parents differ
    for (int k = LOG; k >= 0; k--)
    {
      if (parent[k][a] != parent[k][b])
      {
        a = parent[k][a];
        b = parent[k][b];
      }
    }
    return parent[0][a];
  }

  // Distance formula using LCA
  int distance(int a, int b)
  {
    int L = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[L];
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  Solution solver(n);

  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    solver.addEdge(a, b);
  }

  solver.build();

  while (q--)
  {
    int a, b;
    cin >> a >> b;
    cout << solver.distance(a, b) << "\n";
  }
  return 0;
}
