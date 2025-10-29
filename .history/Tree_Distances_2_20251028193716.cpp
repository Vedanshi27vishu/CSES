#include <bits/stdc++.h>
using namespace std;

/*
 Iterative-safe rerooting solution:
  - subtree: int (<= n)
  - dp: long long (sum of distances can be large)
  - dfs1: iterative to produce postorder (order vector)
  - compute subtree[] and dp[] using postorder
  - dfs2: iterative preorder to reroot and compute dp for children
*/

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  if (!(cin >> n))
    return 0;

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; ++i)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  if (n == 0)
    return 0;
  // iterative DFS to get parent and order (preorder then reversed -> postorder)
  vector<int> parent(n + 1, -1);
  vector<int> order;
  order.reserve(n);

  stack<int> st;
  st.push(1);
  parent[1] = 0;
  while (!st.empty())
  {
    int u = st.top();
    st.pop();
    order.push_back(u);
    for (int v : adj[u])
    {
      if (v == parent[u])
        continue;
      parent[v] = u;
      st.push(v);
    }
  }
  // order currently preorder; reverse to get postorder
  reverse(order.begin(), order.end());

  // subtree sizes (int) and dp values (long long)
  vector<int> subtree(n + 1, 0);
  vector<long long> dp(n + 1, 0);

  // Postorder compute subtree and dp for root=1
  for (int u : order)
  {
    subtree[u] = 1; // count self
    long long sumDpChildren = 0;
    for (int v : adj[u])
    {
      if (v == parent[u])
        continue;
      subtree[u] += subtree[v];
      sumDpChildren += dp[v] + subtree[v];
    }
    dp[u] = sumDpChildren;
  }

  // Reroot iteratively (preorder using stack)
  stack<int> st2;
  st2.push(1);
  while (!st2.empty())
  {
    int u = st2.top();
    st2.pop();
    for (int v : adj[u])
    {
      if (v == parent[u])
        continue;
      // transition: dp[v] = dp[u] - subtree[v] + (n - subtree[v])
      dp[v] = dp[u] - (long long)subtree[v] + (long long)(n - subtree[v]);
      st2.push(v);
    }
  }

  // Output
  for (int i = 1; i <= n; ++i)
  {
    cout << dp[i] << (i == n ? '\n' : ' ');
  }
  return 0;
}
