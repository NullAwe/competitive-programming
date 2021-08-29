#include <bits/stdc++.h>
using namespace std;

void solve() {
  int a, b; cin >> a >> b;
  // Output:
  if ((a + b) % 3 == 0 && b <= a * 2 && a <= b * 2) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
