#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k, sum = 0; cin >> n >> k;
  for (int i = 0; i < n; ++i) { int x; cin >> x; sum += x; }
  cout << (sum ? "YES\n" : "NO\n");
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
