#include <bits/stdc++.h>
using namespace std;

void solve() {
  int l, r; cin >> l >> r;
  int want = r / 2 + 1;
  // Output:
  if (l > want) cout << r - l << endl;
  else cout << r - want << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
