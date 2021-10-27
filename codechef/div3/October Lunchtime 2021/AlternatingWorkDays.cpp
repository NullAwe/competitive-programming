#include <bits/stdc++.h>
using namespace std;

void solve() {
  int a, b, p, q; cin >> a >> b >> p >> q;
  // Output:
  if (p % a || q % b) cout << "NO" << endl;
  else if (abs(p / a - q / b) < 2) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}