#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  // LOG: Maximum power of 2 needed to jump to ancestors
  int LOG = 20;
  vector<vector<int>> up(n + 1, vector<int>(LOG)); // up[v][j] = 2^j-th boss of v
  vector<int> depth(n + 1, 0);

  // Input bosses for employees 2...n
  for (int i = 2; i <= n; i++)
  {
    cin >> up[i][0]; // Direct parent (1-step boss)
  }
  up[1][0] = 1; // root is its own boss when we go up

  // Build binary lifting table
  for (int j = 1; j < LOG; j++)
  {
    for (int v = 1; v <= n; v++)
    {
      up[v][j] = up[up[v][j - 1]][j - 1];
    }
  }

  // Build adjacency list to compute depths
  vector<vector<int>> adj(n + 1);
  for (int i = 2; i <= n; i++)
  {
    adj[up[i][0]].push_back(i);
  }

  // DFS to compute depths
  function<void(int, int)> dfs = [&](int v, int p)
  {
    for (int u : adj[v])
    {
      depth[u] = depth[v] + 1;
      dfs(u, v);
    }
  };
  dfs(1, 1);

  // LCA function (Lowest Common Boss)
  auto lca = [&](int a, int b)
  {
    if (depth[a] < depth[b])
      swap(a, b);

    // 1️⃣ Lift 'a' up to same depth as 'b'
    int diff = depth[a] - depth[b];
    for (int j = 0; j < LOG; j++)
    {
      if (diff & (1 << j))
      {
        a = up[a][j];
      }
    }

    if (a == b)
      return a; // same boss!

    // 2️⃣ Jump both up until just before they meet
    for (int j = LOG - 1; j >= 0; j--)
    {
      if (up[a][j] != up[b][j])
      {
        a = up[a][j];
        b = up[b][j];
      }
    }

    return up[a][0]; // their boss is LCA
  };

  // Process queries
  while (q--)
  {
    int a, b;
    cin >> a >> b;
    cout << lca(a, b) << "\n";
  }

  return 0;
}
