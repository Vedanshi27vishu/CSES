#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO (important for large input)
    cin.tie(nullptr);            // Disable automatic flush after each output

    long long n, k;
    cin >> n >> k; // Read number of elements and window size

    long long x, a, b, c;
    cin >> x >> a >> b >> c; // Read generator parameters

    // We generate array on the fly because storing might be expensive but still required here
    vector<long long> arr(n);
    arr[0] = x; // First element given directly

    // ✅ Generate full input array using the formula
    for (int i = 1; i < n; i++) {
        arr[i] = (a * arr[i - 1] + b) % c;
    }

    // Arrays to store OR values from left and right
    vector<long long> leftOR(n), rightOR(n);

    // ✅ Step 1: Build left ORs
    for (int i = 0; i < n; i++) {
        if (i % k == 0)
            leftOR[i] = arr[i]; // Reset OR when starting a new block of k
        else
            leftOR[i] = leftOR[i - 1] | arr[i]; // OR accumulate inside block
    }

    // ✅ Step 2: Build right ORs
    for (int i = n - 1; i >= 0; i--) {
        if ((i + 1) % k == 0 || i == n - 1)
            rightOR[i] = arr[i]; // Reset OR when reaching block end
        else
            rightOR[i] = rightOR[i + 1] | arr[i]; // OR accumulate backward
    }

    long long ans = 0; // Final XOR result

    // ✅ Step 3: Use precomputed ORs to get each window OR in O(1)
    for (int i = 0; i + k - 1 < n; i++) {
        int j = i + k - 1; // Ending index of the window
        long long OR_value =
            rightOR[i] |      // OR values moving right from start
            leftOR[j];        // OR values moving left from end
        
        ans ^= OR_value; // XOR with final answer accumulator
    }

    cout << ans; // Output the result

    return 0;
}
