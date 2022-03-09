#include <bits/stdc++.h>
using namespace std;

void solve() {
  int l, r, a; cin >> l >> r >> a;
  if ((r + 1) % a == 0 || r / a * a - 1 < l) cout << r / a + r % a << '\n';
  else cout << r / a - 1 + a - 1 << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
