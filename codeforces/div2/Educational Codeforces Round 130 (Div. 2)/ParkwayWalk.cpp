#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m, sum = 0; cin >> n >> m;
  for (int i = 0; i < n; ++i) { int x; cin >> x; sum += x; }
  cout << max(sum - m, 0) << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}