#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k; // input size and window size

    long long x, a, b, c;
    cin >> x >> a >> b >> c; // generator parameters

    long long current = x;   // x1 = x
    long long answer = 0;    // XOR of all window minimums

    deque<pair<long long,int>> dq; // stores {value, index} in increasing order

    // ✅ Build the first window
    dq.push_back({current, 0}); // insert first element

    for(int i = 1; i < k; i++) {
        current = (a * current + b) % c; // generate next number
        
        // Remove elements greater than new value from back (they can't be minimum anymore)
        while(!dq.empty() && dq.back().first > current)
            dq.pop_back();
        
        dq.push_back({current, i}); // insert new element
    }

    answer ^= dq.front().first; // minimum of first window

    // ✅ Slide the window across the array
    for(int i = k; i < n; i++) {
        current = (a * current + b) % c; // generate next number

        // Remove elements out of this window
        while(!dq.empty() && dq.front().second <= i - k)
            dq.pop_front();

        // Remove elements greater than the new element
        while(!dq.empty() && dq.back().first > current)
            dq.pop_back();

        dq.push_back({current, i}); // insert new element
        
        answer ^= dq.front().first; // minimum of current window
    }

    cout << answer << "\n"; // final XOR result
    return 0;
}
