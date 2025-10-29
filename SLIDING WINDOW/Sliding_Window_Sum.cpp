#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Faster IO
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k; // number of elements and window size

    long long x, a, b, c;
    cin >> x >> a >> b >> c; // generator parameters

    long long ans = 0;      // XOR result
    long long windowSum = 0; // current window sum

    vector<long long> window; 
    window.reserve(k); // store only last k values (sliding window)

    // ✅ Step 1: Build first window of size k
    long long current = x; // x1 = x
    window.push_back(current); // push first value
    windowSum += current; // include in sum

    // generate remaining k-1 values
    for (int i = 1; i < k; i++) {
        current = (a * current + b) % c; // generate xi
        window.push_back(current);
        windowSum += current;
    }

    ans ^= windowSum; // first window contributes to XOR

    // ✅ Step 2: Slide the window across the array
    for (int i = k; i < n; i++) {
        long long oldValue = window[i % k]; // value leaving the window

        current = (a * current + b) % c; // generate next xi

        window[i % k] = current; // replace old with new

        windowSum = windowSum - oldValue + current; // update sum in O(1)

        ans ^= windowSum; // add this window's sum to XOR result
    }

    // ✅ Final Output
    cout << ans << "\n";

    return 0;
}
