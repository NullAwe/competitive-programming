#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  set<int> has; for (int i = 1; i <= n; ++i) has.insert(i);
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c;
    has.erase(b);
  }
  int num = *has.begin();
  // Output:
  for (int i = 1; i <= n; ++i) if (i != num) cout << num << ' ' << i << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
