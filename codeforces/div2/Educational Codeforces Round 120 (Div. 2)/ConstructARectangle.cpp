#include <bits/stdc++.h>
using namespace std;

void solve() {
  int a, b, c; cin >> a >> b >> c;
  // Output:
  cout << (a + b == c || b + c == a || c + a == b ||
      (a == b && c % 2 == 0) || (b == c && a % 2 == 0) || (c == a && b % 2 == 0) ? "YES" : "NO") << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
