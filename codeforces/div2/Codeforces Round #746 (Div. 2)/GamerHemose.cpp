#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, h; cin >> n >> h;
  vector<int> d(n); for (int i = 0; i < n; ++i) cin >> d[i];
  sort(d.begin(), d.end());
  int m = d[n - 1], m2 = d[n - 2],
    left = h - (h / (m + m2) * (m + m2)),
    ans = (h / (m + m2)) * 2;
  // Output:
  if (left == 0) cout << ans << endl;
  else if (left <= m) cout << ans + 1 << endl;
  else cout << ans + 2 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}