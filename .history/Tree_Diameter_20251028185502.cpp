#include <bits/stdc++.h>
using namespace std;
// TC: O(N)  SC: O(N)
vector<vector<int>> adj;
int diameter = 0;

// DFS returns height of subtree rooted at 'u'
int dfs(int u, int parent)
{

  int max1 = 0, max2 = 0;
  // max1 = highest child height
  // max2 = second highest child height

  for (int v : adj[u])
  {
    if (v == parent)
      continue; // avoid going back in tree

    int h = dfs(v, u); // height of child's subtree

    // Update top two heights from children
    if (h > max1)
    {
      max2 = max1;
      max1 = h;
    }
    else if (h > max2)
    {
      max2 = h;
    }
  }

  // 🌟 Candidate diameter passing through this node:
  // deepest down one side + deepest down other side
  diameter = max(diameter, max1 + max2);

  // Return height of subtree → longest downward path + this edge
  return max1 + 1;
}

int main()
{
  int n;
  cin >> n;
  adj.assign(n + 1, {});

  // Tree edges input
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1, 0); // root anywhere in a tree

  cout << diameter << endl; // ✅ final longest path in tree
}
