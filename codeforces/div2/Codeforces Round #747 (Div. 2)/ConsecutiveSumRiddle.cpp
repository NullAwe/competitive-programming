#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll n; cin >> n;
  // Output:
  if (n < 0) cout << n << ' ' << -n - 1 << endl;
  else cout << -n + 1 << ' ' << n << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
