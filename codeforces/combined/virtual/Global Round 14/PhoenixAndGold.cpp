#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, x; cin >> n >> x;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int sum = 0;
  vector<int> order(n);
  for (int i = 0; i < n; ++i) {
    sum += arr[i];
    order[i] = arr[i];
    if (sum == x) {
      if (i == n - 1) {
        cout << "NO\n";
        return;
      } else {
        sum += arr[i + 1];
        order[i] = arr[i + 1];
        order[i + 1] = arr[i];
        ++i;
      }
    }
  }
  // Output:
  cout << "YES\n";
  for (int num : order) cout << num << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
