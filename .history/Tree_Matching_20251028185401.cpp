#include <bits/stdc++.h>
using namespace std;
TC: O(N)  SC: O(N)

/*
dp[u][0] = maximum matching in subtree of u when u is NOT matched
dp[u][1] = maximum matching in subtree of u when u IS matched with one of its children
*/
void dfs(int u, int parent, const vector<vector<int>> &adj, vector<array<int, 2>> &dp)
{

  dp[u][0] = 0; // u not matched
  dp[u][1] = 0; // u matched

  // First DFS: compute dp when u is not matched
  for (int v : adj[u])
  {
    if (v == parent)
      continue;
    dfs(v, u, adj, dp);
    dp[u][0] += max(dp[v][0], dp[v][1]); // take best for child
  }

  // Second DFS: try matching u with each child v
  for (int v : adj[u])
  {
    if (v == parent)
      continue;
    // If u matches v -> +1 edge, v must be unmatched
    int candidate = dp[u][0] - max(dp[v][0], dp[v][1]) // subtract previous contribution of v
                    + dp[v][0]                         // v must be unmatched
                    + 1;                               // matched edge u-v

    dp[u][1] = max(dp[u][1], candidate);
  }
}

int main()
{
  int n;
  cin >> n;

  // adjacency list
  vector<vector<int>> adj(n + 1);

  // dp array initialized to zeros
  vector<array<int, 2>> dp(n + 1);

  // input tree edges
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // Run DFS from root = 1 (any node works since it's a tree)
  dfs(1, -1, adj, dp);

  // ans = best option for root (matched or not)
  cout << max(dp[1][0], dp[1][1]) << "\n";
  return 0;
}
