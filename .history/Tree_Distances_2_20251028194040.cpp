#include <bits/stdc++.h>
using namespace std;

/*
dfs1 (Post-order DFS):
- Calculates:
    subtree[u] = number of nodes in subtree of u
    dp[u] = sum of distances from u to all nodes in its subtree
*/
void dfs1(int u, int parent, vector<vector<int>> &adj, vector<long long> &subtree, vector<long long> &dp)
{
  subtree[u] = 1; // include itself
  dp[u] = 0;

  for (int v : adj[u])
  {
    if (v == parent)
      continue; // avoid back edge

    dfs1(v, u, adj, subtree, dp);

    subtree[u] += subtree[v];    // add child's subtree size
    dp[u] += dp[v] + subtree[v]; // distances increase by subtree[v]
  }
}

/*
dfs2 (Rerooting DFS):
- We reuse parent result to compute child dp faster
Formula:
dp[v] = dp[u]               // parent's sum
        - subtree[v]        // nodes that got 1 closer when moving root
        + (n - subtree[v]); // other nodes go 1 farther from v
*/
void dfs2(int u, int parent, vector<vector<int>> &adj, vector<int> &subtree, vector<int> &dp, int n)
{
  for (int v : adj[u])
  {
    if (v == parent)
      continue;

    // Reroot DP transition formula
    dp[v] = dp[u] - subtree[v] + (n - subtree[v]);

    dfs2(v, u, adj, subtree, dp, n);
  }
}

int main()
{
  int n;
  cin >> n;

  // adjacency list
  vector<vector<int>> adj(n + 1);

  // read edges
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

   vector<int> subtree(n + 1);
    vector<long long> dp(n + 1);

  // Step 1: Calculate dp and subtree size from root = 1
  dfs1(1, 0, adj, subtree, dp);

  // Step 2: Re-root DP for all nodes
  dfs2(1, 0, adj, subtree, dp, n);

  // Output final result
  for (int i = 1; i <= n; i++)
    cout << dp[i] << " ";

  return 0;
}
// Rerooting DP formula bas yahi count karta hai ki kise ek step door aur kise ek step paas le ja rahe ho jab root change hota hai.