#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n, m, k; cin >> n >> m >> k;
    --k;
    vector<string> grid(n);
    for (int ii = 0; ii < n; ++ii) cin >> grid[ii];
    int ans = 0;
    for (int j = 0; j < m; ++j) if (grid[k][j] == 'X') ++ans;
    vector<int> above(m);
    for (int ii = 0; ii <= k; ++ii) for (int jj = 0; jj < m; ++jj)
      if (grid[ii][jj] == 'X') ++above[jj];
    for (int shift = 1; shift <= k; ++shift) {
      int thisAns = 0;
      for (int j = 0; j < m; ++j)
        if (above[j] > k || (k + shift < n &&
              grid[k + shift][j] == 'X')) ++thisAns;
      thisAns += shift;
      ans = min(ans, thisAns);
      for (int j = 0; j < m; ++j)
        if (k + shift < n && grid[k + shift][j] == 'X') ++above[j];
    }
    vector<int> below(m);
    for (int ii = k; ii < n; ++ii) for (int jj = 0; jj < m; ++jj)
      if (grid[ii][jj] == 'X') ++below[jj];
    for (int shift = 1; shift <= n - k - 1; ++shift) {
      int thisAns = 0;
      for (int j = 0; j < m; ++j)
        if (below[j] > n - k - 1 || (k - shift >= 0 &&
              grid[k - shift][j] == 'X')) ++thisAns;
      thisAns += shift;
      ans = min(ans, thisAns);
      for (int j = 0; j < m; ++j)
        if (k - shift >= 0 && grid[k - shift][j] == 'X') ++below[j];
    }
    // Output:
    cout << "Case #" << i << ": " << ans << endl;
  }
  return 0;
}
