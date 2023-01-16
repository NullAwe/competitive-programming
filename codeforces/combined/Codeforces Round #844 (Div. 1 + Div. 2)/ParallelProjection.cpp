#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int w, d, h; cin >> w >> d >> h;
  int a, b, f, g; cin >> a >> b >> f >> g;
  cout << h + min(abs(a - f) + min(b + g, d - b + d - g), abs(b - g) + min(a + f, w - a + w - f)) << '\n';
  
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
