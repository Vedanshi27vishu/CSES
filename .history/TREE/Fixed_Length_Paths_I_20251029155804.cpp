// #include <bits/stdc++.h>
// using namespace std;

// int n, k;
// vector<vector<int>> adj;
// vector<int> depthCount;
// long long ans = 0;

// // DFS that fills depthCount[] with number of nodes at each depth
// void dfs(int u, int p, int depth)
// {
//   if (depth > k)
//     return; // no need deeper than k
//   depthCount[depth]++;
//   for (int v : adj[u])
//     if (v != p)
//       dfs(v, u, depth + 1);
// }

// int main()
// {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);

//   cin >> n >> k;
//   adj.assign(n + 1, {});

//   // input edges
//   for (int i = 0; i < n - 1; i++)
//   {
//     int a, b;
//     cin >> a >> b;
//     adj[a].push_back(b);
//     adj[b].push_back(a);
//   }

//   // Try each node as potential center (TREE ROOT)
//   for (int center = 1; center <= n; center++)
//   {
//     depthCount.assign(k + 1, 0);

//     // DFS from center
//     for (int v : adj[center])
//     {
//       vector<int> sub(k + 1, 0);

//       // Compute depth distribution of this subtree
//       dfs(v, center, 1);

//       // Combine with earlier subtrees
//       for (int d = 1; d <= k; d++)
//       {
//         if (d <= k)
//           ans += 1LL * depthCount[d] * sub[k - d];
//       }

//       // Merge sub into global depthCount
//       for (int d = 1; d <= k; d++)
//         depthCount[d] += sub[d];
//     }
//   }

//   cout << ans << "\n";
//   return 0;
// }
