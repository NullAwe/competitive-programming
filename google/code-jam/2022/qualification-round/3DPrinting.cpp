#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
  int a[4], b[4], c[4], ans[4], sum = 0, total = 1e6;
  for (int i = 0; i < 4; ++i) cin >> a[i];
  for (int i = 0; i < 4; ++i) cin >> b[i];
  for (int i = 0; i < 4; ++i) cin >> c[i];
  for (int i = 0; i < 4; ++i) ans[i] = min(min(min(a[i], b[i]), c[i]), total - sum), sum += ans[i];
  if (sum < total) cout << "Case #" << t << ": IMPOSSIBLE\n";
  else cout << "Case #" << t << ": " << ans[0] << ' ' << ans[1] << ' ' << ans[2] << ' ' << ans[3] << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
  return 0;
}
