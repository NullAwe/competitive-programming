#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, mx = 0, g = 0; cin >> n;
  for (int i = 0; i < n; ++i) {int x; cin >> x; mx = max(mx, x), g = gcd(g, x);}
  cout << mx / g << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
