#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> m(101);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    ++m[abs(a)];
  }
  int ans = min(m[0], 1);
  for (int i = 1; i < 101; ++i) ans += min(m[i], 2);
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
