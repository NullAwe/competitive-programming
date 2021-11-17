#include <bits/stdc++.h>
using namespace std;

void solve() {
  int a, b, c; cin >> a >> b >> c;
  int val = abs(a + b - 2 * c);
  // Output:
  cout << (val % 3 ? 1 : 0) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
