#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<ll> a(n), b(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  ll zz = abs(a[0] - b[0]), zn = abs(a[0] - b[n - 1]), nz = abs(a[n - 1] - b[0]), nn = abs(a[n - 1] - b[n - 1]);
  ll ca0 = INT_MAX, can = INT_MAX, cb0 = INT_MAX, cbn = INT_MAX;
  for (int i = 0; i < n; ++i) ca0 = min(ca0, abs(a[0] - b[i])), can = min(can, abs(a[n - 1] - b[i])), cb0 = min(cb0, abs(a[i] - b[0])), cbn = min(cbn, abs(a[i] - b[n - 1]));
  ll ans = min(zz + nn, zn + nz);
  ans = min(ans, ca0 + can + cb0 + cbn);
  ans = min(ans, zz + can + cbn);
  ans = min(ans, nn + ca0 + cb0);
  ans = min(ans, zn + can + cb0);
  ans = min(ans, nz + ca0 + cbn);
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
