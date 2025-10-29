#include <bits/stdc++.h>
using namespace std;
// 
vector<vector<int>> adj; // adjacency list for tree

// DFS function to calculate subtree sizes
int dfs(int node, int parent, vector<int> &subtree)
{
  subtree[node] = 1; // each node contributes 1 to its subtree size

  // Traverse all its children (adjacent nodes except parent)
  for (int child : adj[node])
  {
    if (child == parent)
      continue;
    subtree[node] += dfs(child, node, subtree);
  }

  return subtree[node];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  adj.assign(n + 1, {}); // Resize adjacency list

  // Read edges (tree so exactly n-1 edges)
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> subtree(n + 1);

  // ✅ Step 1: Run DFS from any node (1 here) to compute subtree sizes
  dfs(1, -1, subtree);

  int centroid = 1; // default (we will check and update)

  // ✅ Step 2: Check each node if it can be centroid
  for (int node = 1; node <= n; node++)
  {
    int maxPart = 0; // largest part after removing this node

    // Check sizes of all subtrees formed by removing this node
    for (int child : adj[node])
    {
      if (subtree[child] < subtree[node])
      {
        // child subtree is separate part
        maxPart = max(maxPart, subtree[child]);
      }
    }

    // Remaining part of the tree excluding subtree of this node
    int remaining = n - subtree[node];
    maxPart = max(maxPart, remaining);

    // ✅ If the largest remaining part is ≤ n/2 → this node is a centroid
    if (maxPart <= n / 2)
    {
      centroid = node;
      break; // we can stop because any valid centroid is fine
    }
  }

  // Output centroid
  cout << centroid << "\n";
  return 0;
}
