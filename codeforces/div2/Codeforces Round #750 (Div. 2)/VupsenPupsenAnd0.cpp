#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  if (n % 2 == 0) {
    // Output:
    for (int i = 0; i < n; ++i) {
      if (i < n / 2) cout << arr[n - i - 1] << ' ';
      else cout << -arr[n - i - 1] << ' ';
    }
    cout << endl;
  } else {
    int sum = arr[n / 2 - 1] + arr[n / 2 + 1], midSum = arr[n / 2];
    int left = -midSum, middle = sum, right = -midSum;
    if (sum == 0) {
      left = -arr[n / 2] + 1, middle = arr[n / 2 - 1], right = 1;
      if (arr[n / 2] == 1) {
        left = 2, middle = -arr[n / 2 - 1], right = 1;
      }
    }
    // Output:
    for (int i = 0; i < n; ++i) {
      if (i < n / 2 - 1) cout << arr[n - i - 1] << ' ';
      else if (i > n / 2 + 1) cout << -arr[n - i - 1] << ' ';
      else if (i == n / 2) cout << middle << ' ';
      else if (i == n / 2 - 1) cout << left << ' ';
      else cout << right << ' ';
    }
    cout << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}