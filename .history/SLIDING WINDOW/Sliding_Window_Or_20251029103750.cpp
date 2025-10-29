#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<long long> arr(n);
    arr[0] = x;  // First value

    // ✅ Generate array using the formula
    for (int i = 1; i < n; i++) {
        arr[i] = (a * arr[i - 1] + b) % c;
    }

    vector<long long> leftOR(n), rightOR(n);

    // ✅ Build left OR (reset every k elements)
    for (int i = 0; i < n; i++) {
        if (i % k == 0) 
            leftOR[i] = arr[i];
        else 
            leftOR[i] = leftOR[i - 1] | arr[i];
    }

    // ✅ Build right OR (reset every k elements)
    for (int i = n - 1; i >= 0; i--) {
        if ((i + 1) % k == 0 || i == n - 1) 
            rightOR[i] = arr[i];
        else 
            rightOR[i] = rightOR[i + 1] | arr[i];
    }

    long long ans = 0;

    // ✅ Calculate window OR using boundaries
    for (int i = 0; i + k - 1 < n; i++) {
        long long OR_val = rightOR[i] | leftOR[i + k - 1];
        ans ^= OR_val;  // XOR all results
    }

    cout << ans;
    return 0;
}
