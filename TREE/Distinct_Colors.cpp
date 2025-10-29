#include <bits/stdc++.h>
using namespace std;

vector<int> ans; // final answer for each node

// DFS returns a pointer to a set containing unique colors in this subtree
set<int> *dfs(int u, int parent, vector<vector<int>> &adj, vector<int> &color)
{

  set<int> *mySet = new set<int>(); // this node's set initially empty
  mySet->insert(color[u]);          // add my own color

  for (int v : adj[u])
  {
    if (v == parent)
      continue;

    set<int> *childSet = dfs(v, u, adj, color);

    // ✅ Small-to-Large merging
    if (childSet->size() > mySet->size())
      swap(childSet, mySet);

    // merge smaller child set into bigger one
    for (int c : *childSet)
      mySet->insert(c);

    delete childSet; // free memory
  }

  ans[u] = mySet->size(); // store result for this node
  return mySet;           // return pointer of the big set
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> color(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> color[i];

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  ans.assign(n + 1, 0);

  dfs(1, 0, adj, color);

  for (int i = 1; i <= n; i++)
    cout << ans[i] << " ";

  return 0;
}
