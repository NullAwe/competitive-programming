#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k; --k;
  vector<string> grid(n); for (int i = 0; i < n; ++i) cin >> grid[i];
  vector<set<int>> ones(n);
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (abs(i - j) > n - k) continue;
    if (grid[i][j] == '0') ones[j].insert(i);
  }
  int _x = n - k, _y = 0;
  vector<vector<bool>> pathed(n, vector<bool>(n));
  for (int add = 0; add < k; ++add) {
    int x = _x + add, y = _y + add;
    while (y <= _x + add) {
      int nx = x;
      if (ones[y].size()) {
        auto it = ones[y].upper_bound(x);
        if (it != ones[y].begin()) {
          nx = *ones[y].begin();
          while (ones[y].size() && *ones[y].begin() <= x) ones[y].erase(ones[y].begin());
        }
      }
      for (int i = nx; i <= x; ++i) pathed[i][y] = true;
      x = nx, ++y;
    }
    for (int i = _y + add; i <= x; ++i) pathed[i][y - 1] = true;
  }
  for (int i = 0; i < n; ++i) {
    if (ones[i].size()) {
      cout << "NO\n";
      return;
    }
  }
  vector<vector<bool>> ans(n, vector<bool>(n));
  int offed = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (abs(i - j) > n - k || pathed[i][j]) ans[i][j] = 1;
      else ++offed;
    }
  }
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
    if (offed < (n - k) * (n - k) && ans[i][j] && grid[i][j] == '1') ans[i][j] = 0, ++offed;
  if (offed < (n - k) * (n - k)) cout << "NO\n";
  else {
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) cout << ans[i][j];
      cout << '\n';
    }
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}