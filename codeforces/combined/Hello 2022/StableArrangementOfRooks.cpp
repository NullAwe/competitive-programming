#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  if (k > (n + 1) / 2) {
    cout << "-1\n";
    return;
  }
  vector<vector<char>> ans(n, vector<char>(n, '.'));
  for (int i = 0; i < k; ++i) ans[i * 2][i * 2] = 'R';
  // Output:
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cout << ans[i][j];
    cout << '\n';
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
