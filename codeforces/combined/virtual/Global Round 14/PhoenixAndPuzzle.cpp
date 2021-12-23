#include <bits/stdc++.h>
using namespace std;

int sq(int x) { return x * x; }

void solve() {
  int n; cin >> n;
  // Output:
  if ((n % 2 == 0 && sq((int) sqrt(n / 2)) == n / 2) ||
      (n % 4 == 0 && sq((int) sqrt(n / 4)) == n / 4)) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
