#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int ans = -1;
  for (int i = 0; i < n; ++i) {
    if (arr[i] == i) continue;
    ans = ans < 0 ? arr[i] : ans & arr[i];
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
