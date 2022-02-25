#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  if (n % 2 == 0) cout << 2 << ' ' << n - 3;
  else if (n % 4 == 1) cout << n / 2 - 1 << ' ' << n / 2 + 1;
  else cout << n / 2 - 2 << ' ' << n / 2 + 2;
  cout << " 1\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
