#include <bits/stdc++.h> // Import everything quickly for competitive programming
using namespace std;

const int MOD = 1e9 + 7; // Modulo given in problem

// Fenwick Tree (Binary Indexed Tree) to maintain prefix sums efficiently
struct Fenwick {
    int n;                     // Size of Fenwick Tree (number of indexes)
    vector<long long> bit;     // BIT array to store prefix result values

    // Initialize Fenwick tree with size n
    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    // Update index i by adding value 'val'
    void update(int i, long long val) {
        while (i <= n) {             // Move upward in BIT until out of bounds
            bit[i] = (bit[i] + val) % MOD; // Add value safely with modulo
            i += i & -i;             // Jump to next responsible index (LSB trick)
        }
    }

    // Query sum from index 1 to i
    long long query(int i) {
        long long s = 0;             // Result sum
        while (i > 0) {              // Move downward through BIT
            s = (s + bit[i]) % MOD;  // Add values stored in BIT
            i -= i & -i;             // Move to parent index (LSB trick)
        }
        return s;                    // Return computed sum
    }
};

int main() {
    ios::sync_with_stdio(false); // Faster I/O
    cin.tie(nullptr);            // Avoid flushing unnecessary output

    int n;
    cin >> n;                    // Read number of elements

    vector<int> a(n);            // Original array
    for (int i = 0; i < n; i++)
        cin >> a[i];             // Input array values

    // We must compress values because they can be up to 1e9
    vector<int> sorted_vals = a; // Copy array for sorting unique values
    sort(sorted_vals.begin(), sorted_vals.end()); // Sort values
    sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()),
                      sorted_vals.end()); // Remove duplicates → compressed list

    // Replace each number by its compressed rank (1-based index)
    for (int i = 0; i < n; i++)
        a[i] = lower_bound(sorted_vals.begin(), 
                           sorted_vals.end(), 
                           a[i]) - sorted_vals.begin() + 1; // Convert to rank

    Fenwick ft(sorted_vals.size()); // Fenwick tree sized to unique values count

    long long result = 0;           // Final answer → total increasing subsequences

    // Process each element one by one to calculate dp values
    for (int i = 0; i < n; i++) {

        // Query sum of dp values for all elements < current (strictly increasing)
        long long smaller = ft.query(a[i] - 1);

        // dp[i] = (all ways ending with smaller values) + standalone element
        long long dp = (smaller + 1) % MOD;

        result = (result + dp) % MOD; // Add dp[i] to global answer

        ft.update(a[i], dp);    // Store dp[i] for future usage in BIT
    }

    cout << result << "\n";     // Print final answer
    return 0;                   // Successful end of program
}
