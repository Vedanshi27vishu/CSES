#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  int LOG = 20; // Since 2^18 > 2e5 (enough to binary lifting any node)
  vector<vector<int>> up(n + 1, vector<int>(LOG, -1));
  // up[x][j] = 2^j th boss of employee x

  // Input: bosses for employees 2..n
  for (int i = 2; i <= n; i++)
  {
    cin >> up[i][0]; // direct boss (2^0 = 1 level up)
  }

  up[1][0] = -1; // CEO has no boss

  // STEP 1️⃣: Precompute Binary Lifting table
  for (int j = 1; j < LOG; j++)
  {
    for (int i = 1; i <= n; i++)
    {
      if (up[i][j - 1] != -1)
        up[i][j] = up[up[i][j - 1]][j - 1];
      // Move i up by 2^j using predecessor of 2^(j-1)
    }
  }

  // Function: jump x up by k levels
  auto lift = [&](int x, int k)
  {
    for (int j = 0; j < LOG; j++)
    {
      if (k & (1 << j))
      { // If bit j is set → jump 2^j steps
        x = up[x][j];
        if (x == -1)
          break;
      }
    }
    return x;
  };

  // STEP 2️⃣: Answer queries
  while (q--)
  {
    int x, k;
    cin >> x >> k;
    int ans = lift(x, k);
    cout << ans << "\n";
  }

  return 0;
}
