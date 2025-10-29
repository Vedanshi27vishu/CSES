#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast input/output
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // Read array
    }

    unordered_map<int,int> freq; // Stores frequency of elements in window
    vector<int> result;          // Stores distinct count of each window

    // ✅ Step 1: Build first window of size k
    for (int i = 0; i < k; i++) {
        freq[arr[i]]++; // Increment count for each element
    }
    result.push_back(freq.size()); // First window answer

    // ✅ Step 2: Slide the window from index 1 to n-k
    for (int i = k; i < n; i++) {

        int outElem = arr[i - k]; // Element that is leaving window
        freq[outElem]--;          // Reduce its freq
        if (freq[outElem] == 0) {
            freq.erase(outElem);  // Remove if not present anymore
        }

        int inElem = arr[i];      // New element entering window
        freq[inElem]++;           // Increase its freq

        result.push_back(freq.size()); // Distinct count after sliding
    }

    // ✅ Output the results
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    
    return 0;
}
