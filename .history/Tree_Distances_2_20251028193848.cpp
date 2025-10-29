#include <bits/stdc++.h>
using namespace std;

void dfs1(int u, int parent, vector<vector<int>> &adj,
          vector<int> &subtree, vector<long long> &dp)
{

  subtree[u] = 1;
  dp[u] = 0;

  for (int v : adj[u])
  {
    if (v == parent)
      continue;

    dfs1(v, u, adj, subtree, dp);

    subtree[u] += subtree[v];
    dp[u] += dp[v] + subtree[v];
  }
}

void dfs2(int u, int parent, vector<vector<int>> &adj,
          vector<int> &subtree, vector<long long> &dp, int n)
{

  for (int v : adj[u])
  {
    if (v == parent)
      continue;

    dp[v] = dp[u] - subtree[v] + (long long)(n - subtree[v]);

    dfs2(v, u, adj, subtree, dp, n);
  }
}

int main()
{
  int n;
  cin >> n;

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> subtree(n + 1);
  vector<long long> dp(n + 1);

  dfs1(1, 0, adj, subtree, dp);
  dfs2(1, 0, adj, subtree, dp, n);

  for (int i = 1; i <= n; i++)
    cout << dp[i] << " ";
}
