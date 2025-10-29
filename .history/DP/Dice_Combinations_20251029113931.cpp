#include <bits/stdc++.h>   // Includes all standard libraries
using namespace std;

const int MOD = 1e9 + 7;   // Modulo value as required

int main() {
    ios::sync_with_stdio(false); // Fast I/O
    cin.tie(nullptr);

    int n;
    cin >> n;                // Read the target sum

    vector<long long> dp(n + 1, 0); // dp[i] = number of ways to make sum i
    dp[0] = 1;               // Base case: one way to make sum 0 (empty throw)

    // Compute dp values from 1 to n
    for (int i = 1; i <= n; i++) {
        // Try adding every dice value from 1 to 6
        for (int dice = 1; dice <= 6; dice++) {
            if (i - dice >= 0) {     // Check valid remaining sum
                dp[i] = (dp[i] + dp[i - dice]) % MOD; // Add ways from i - dice
            }
        }
    }

    cout << dp[n]; // Final result for sum n
    return 0;
}
