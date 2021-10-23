#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  ll x, k; cin >> x >> k;
  // Output:
  cout << x * 2 << ' ' << (x * k - 1) * (x * k) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
