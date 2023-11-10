#include <bits/stdc++.h>
using namespace std;

#define int long long

int solveA(int x, int y) {
  if (x == 0) return 0;
  if (y == 0) return x;
  if (x % y == 0) return x / y + y - 1;
  if (x > y) return x / y + (y - 1) / (x % y) + solveA(x % y, y);
  return solveA(x, y % x);
}

int solveB(int x, int y) {
  if (x == 0) return 0;
  if (y == 0) return x;
  if (x % y == 0) return y;
  if (x > y) return (y - 1) / (x % y) + solveB(x % y, y);
  return solveB(x, y % x);
}

void solve() {
  int x, y; cin >> x >> y;
  cout << (y + x - 1) / x + solveA(x, y) + solveB(x, y) - 2 << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
