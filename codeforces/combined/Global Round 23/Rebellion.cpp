#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, ones = 0, ans = 0; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) { cin >> arr[i]; ones += arr[i]; }
  for (int i = 0; i + ones < n; ++i) ans += arr[i];
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
