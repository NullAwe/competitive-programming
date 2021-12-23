#include <bits/stdc++.h>
using namespace std;

void solve() {
  int r, n; cin >> r >> n;
  // Takes care of the edge case where there is only one spot:
  if (r == 1) {
    cout << n << endl;
    return;
  }
  vector<pair<int, pair<int, int>>> c(n);
  for (int i = 0; i < n; ++i) cin >> c[i].first >> c[i].second.first >> c[i].second.second;
  // Finds the answer using dynamic programming:
  vector<int> memo(n, 1);
  int m = 0;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < min(i + 2 * r - 2, n); ++j)
      if (c[j].first - c[i].first >=
          abs(c[j].second.first - c[i].second.first) +
          abs(c[j].second.second - c[i].second.second)) memo[i] = max(memo[i], memo[j] + 1);
    if (i + 2 * r - 2 < n) m = max(m, memo[i + 2 * r - 2]);
    memo[i] = max(memo[i], m + 1);
  }
  int ans = 0;
  for (int i = 0; i < n; ++i)
    if (c[i].first >= abs(c[i].second.first - 1) + abs(c[i].second.second - 1)) ans = max(ans, memo[i]);
  // Output:
  cout << ans << endl;
}

int main() {
  solve();
  return 0;
}
