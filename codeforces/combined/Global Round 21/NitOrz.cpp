#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, z, ans = 0; cin >> n >> z;
  for (int i = 0; i < n; ++i) { int x; cin >> x; ans = max(ans, x | z); }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
