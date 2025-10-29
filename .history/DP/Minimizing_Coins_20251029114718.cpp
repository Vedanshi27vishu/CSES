#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i]; // storing each coin value
    }

    // We will use Dynamic Programming (Bottom-Up approach)
    // dp[i] = minimum number of coins needed to form sum i
    // If dp[i] is very large → sum i is not possible to form

    const int INF = 1e9; // a large number used to represent impossible state

    // Initialize DP array of size x+1 (because we need dp[x] result)
    vector<int> dp(x + 1, INF);

    // Base Case:
    // To form sum 0 → we don't need any coin
    dp[0] = 0;

    // Try to form every sum from 1 to x
    for (int i = 1; i <= x; i++) {
        // For each sum i, try using every coin
        for (int coin : coins) {

            // We can only use the coin if i - coin is not negative
            // which means previous state exists
            if (i - coin >= 0) {
                // If we use this coin → add 1 coin to dp[i - coin]
                // Take the minimum among all options
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    // If dp[x] is still INF → we never updated it → impossible to form x
    if (dp[x] >= INF) {
        cout << -1 << "\n"; // print -1 for no solution
    }
    else {
        cout << dp[x] << "\n"; // otherwise print the minimum coins required
    }

    return 0;
}
