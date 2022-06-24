#include <iostream>
using namespace std;

void solve() {
  int n, ans = 0; cin >> n;
  for (int i = 0; i < n; ++i) { int x; cin >> x; ans += x & 1; }
  cout << (ans ? "first" : "second") << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

