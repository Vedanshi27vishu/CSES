#include <bits/stdc++.h>
using namespace std;
#define ll long long

void dfs(int v, vector<vector<int>> &adj, vector<int> &dp, vector<int> &visited)
{
  int ans = 0;
  visited[v] = true;
  for (int x : adj[v])
  {
    if (!visited[x])
    {
      dfs(x, adj, dp, visited);
      ans = 1 + dp[x];
    }
  }
  dp[v] = ans;
}

signed main()
{
  int n;
  cin >> n;
  vector<vector<int>> adj(n + 1);
  int st = 2;
  for (int i = 0; i < n - 1; i++)
  {
    int k;
    cin >> k;
    adj[k].push_back(st);
    st++;
  }

  vector<int> dp(n + 1, 0);
  vector<int> visited(n + 1, 0);
  dfs(1, adj, dp, visited);
  for (int i = 1; i <= n; i++)
    cout << dp[i] << " ";
}
