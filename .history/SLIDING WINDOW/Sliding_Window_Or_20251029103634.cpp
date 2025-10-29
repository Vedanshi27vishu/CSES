#include <bits/stdc++.h>          // Import all standard libraries
using namespace std;

int main() {
    ios::sync_with_stdio(false);  // Fast input-output
    cin.tie(nullptr);             // Untie cin from cout to speed up

    long long n, k;
    cin >> n >> k;                // Read number of elements and window size

    long long x, a, b, c;
    cin >> x >> a >> b >> c;      // Parameters for generating array

    long long result = 0;         // Final XOR of all window OR values

    deque<long long> dq;          // Will store useful elements for OR calculation
    vector<long long> arr(n);     // Storing generated values

    arr[0] = x;                   // First element given directly

    // ✅ Generate the full array on the fly using the formula
    for (int i = 1; i < n; i++) {
        arr[i] = (a * arr[i - 1] + b) % c; // Generator relation
    }

    // ✅ Process elements one by one
    for (int i = 0; i < n; i++) {

        // Remove elements from the back that are smaller
        // because they won't contribute in future OR results
        while (!dq.empty() && dq.back() < arr[i])
            dq.pop_back();

        dq.push_back(arr[i]);     // Add current element into deque

        // Remove elements that are out of current window range
        if (i >= k && dq.front() == arr[i - k])
            dq.pop_front();

        // Start giving OR results only after first full window
        if (i >= k - 1)
            result ^= dq.front(); // XOR the maximum OR value
    }

    cout << result;               // Print final answer
    return 0;
}
