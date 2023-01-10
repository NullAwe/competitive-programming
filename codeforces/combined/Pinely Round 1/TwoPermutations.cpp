#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, a, b; cin >> n >> a >> b;
  if (a == b && a == n) cout << "YES\n";
  else if (a + b >= n - 1) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
