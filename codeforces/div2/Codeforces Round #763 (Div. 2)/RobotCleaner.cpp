#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m, rb, cb, rd, cd; cin >> n >> m >> rb >> cb >> rd >> cd;
  // Output:
  cout << min((rb <= rd ? rd - rb : n + n - rb - rd), (cb <= cd ? cd - cb : m + m - cb - cd)) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
