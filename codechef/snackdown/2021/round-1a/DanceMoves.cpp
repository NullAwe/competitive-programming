#include <bits/stdc++.h>
using namespace std;

void solve() {
  int a, b; cin >> a >> b;
  // Output:
  if (a > b) cout << a - b << endl;
  else cout << (b - a) / 2 + ((b - a) % 2 * 2) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
