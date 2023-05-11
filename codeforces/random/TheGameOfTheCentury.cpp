#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string a, b, c; cin >> a >> b >> c;
  if (a.back() == b.back() && b.back() == c.back()) {
    cout << 0 << '\n';
    return;
  }
  if (c.back() == '1' && a.back() == '0') swap(a, c), swap(a, b);
  else if (a.back() == '1' && b.back() == '0') swap(a, b), swap(a, c);
  if (a.back() == '0') {
    swap(b, c);
    for (int i = 0; i < n; ++i) {
      a[i] = (char) ('0' + '1' - a[i]);
      b[i] = (char) ('0' + '1' - b[i]);
      c[i] = (char) ('0' + '1' - c[i]);
    }
  }
  int ans = n;
  for (int i = n - 1; i >= 0; --i)
    if (c[i] == '1') ans = min(ans, 2 * (n - i - 1));
  int xx = -1, yy = -1;
  for (int i = n - 1; i >= 0; --i) {
    if (xx < 0 && b[i] == '0') xx = n - i - 1;
    if (yy < 0 && a[i] == '0') yy = n - i - 1;
  }
  if (xx >= 0 && yy >= 0) ans = min(ans, xx + yy);
  yy = -1;
  for (int i = n - 1; i >= 0; --i) if (yy < 0 && c[i] == '1') yy = n - i - 1;
  if (xx >= 0 && yy >= 0) ans = min(ans, xx + yy);
  int l0 = -1;
  for (int j = n - 2; j >= 0; --j)
    if (l0 < 0 && a[j] == '0') l0 = j;
  if (l0 >= 0)
    for (int i = n - l0 - 2; i < n - 1; ++i)
      if (c[i] == '1') ans = min(ans, n - i - 1 + n - l0 - 1);
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}