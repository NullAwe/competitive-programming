#include <bits/stdc++.h>
using namespace std;

void solve() {
  int c, d; cin >> c >> d;
  // Output:
  if (c == 0 && d == 0) cout << 0 << endl;
  else if (c == d) cout << 1 << endl;
  else if (abs(c - d) % 2 == 1) cout << -1 << endl;
  else cout << 2 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
