#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> sorted = arr;
  sort(sorted.begin(), sorted.end());
  for (int i = n - k; i < k; ++i) {
    if (arr[i] != sorted[i]) {
      // Output:
      cout << "NO" << endl;
      return;
    }
  }
  // Output:
  cout << "YES" << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}