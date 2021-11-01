#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  int lo = 0, hi = n + 5;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    ll m = mid * (mid + 1) / 2 + 1;
    if (m <= n) lo = (int) mid;
    else hi = (int) mid;
  }
  // Output:
  cout << hi * 2 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
