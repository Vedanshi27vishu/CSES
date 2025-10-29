#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    long long windowXOR = 0;     // XOR of current sliding window
    long long final_xor = 0;     // XOR of all window XORs
    queue<long long> q;          // To remember elements inside the window

    // Process each element
    for(long long i = 1; i <= n; i++) {
        long long value = x;     // Current generated element

        // Add new element into window
        windowXOR ^= value;
        q.push(value);

        // If window size exceeds k, remove the oldest element
        if(q.size() > k) {
            windowXOR ^= q.front();
            q.pop();
        }

        // When window is of exact size k → take XOR in answer
        if(i >= k) {
            final_xor ^= windowXOR;
        }

        // Generate next element
        x = (a * x + b) % c;
    }

    cout << final_xor;
    return 0;
}
