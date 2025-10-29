#include <bits/stdc++.h>
using namespace std;

// DFS to compute dp[v] = 1 + max depth of any child
void dfs(int v, vector<vector<int>> &adj, vector<int> &dp, vector<bool> &visited)
{

  visited[v] = true;
  int ans = 0; // max depth from any child node

  // Traverse all adjacent / connected nodes
  for (int x : adj[v])
  {

    if (!visited[x])
    {
      dfs(x, adj, dp, visited);

      // dp[x] contains max depth from child x
      ans = max(ans, 1 + dp[x]);
    }
  }

  dp[v] = ans; // store computed depth for node v
}

int main()
{

  int n;
  cin >> n;

  vector<vector<int>> adj(n + 1);

  // Creating a tree where node 1 is root
  // and edges are: 1-2, 2-3, 3-4 ... (like a chain)
  int st = 2;
  for (int i = 0; i < n - 1; i++)
  {
    int k;
    cin >> k;
    adj[k].push_back(st);
    st++;
  }

  vector<int> dp(n + 1, 0);
  vector<bool> visited(n + 1, false);

  dfs(1, adj, dp, visited);

  // Print depth values of every node
  for (int i = 1; i <= n; i++)
    cout << dp[i] << " ";

  return 0;
}
