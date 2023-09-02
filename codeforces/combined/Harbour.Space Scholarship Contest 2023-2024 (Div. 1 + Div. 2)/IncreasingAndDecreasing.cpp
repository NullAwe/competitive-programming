#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int x, y, n; cin >> x >> y >> n;
  vector<int> arr(n); arr[0] = x;
  for (int i = 1; i < n; ++i) arr[i] = arr[i - 1] + n - i;
  if (arr.back() > y) cout << -1 << '\n';
  else {
    for (int i = 1; i < n; ++i) arr[i] += y - arr.back();
    for (int num : arr) cout << num << ' ';
    cout << '\n';
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
