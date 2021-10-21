#include <bits/stdc++.h>
using namespace std;

void solve() {
  int a, b, c; cin >> a >> b >> c;
  // Output:
  if (a == 7 || b == 7 || c == 7) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
