#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  // Finds the answer using brute force:
  for (int i = 0; true; ++i) {
    // Checks if the array is sorted:
    bool sorted = true;
    for (int j = 0; j < n - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        sorted = false;
        break;
      }
    }
    if (sorted) {
      // Output:
      cout << i << endl;
      return;
    }
    // Performs swaps as outlined in the problem:
    for (int j = i % 2; j < n - 1; j += 2) {
      if (arr[j] > arr[j + 1]) {
        int tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
    }
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
