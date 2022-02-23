#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, x; cin >> n >> x;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<int>> dp(n + 1, vector<int>(n + 1));
  int cur = 0;
  for (int i = 0; i < n; ++i) {
    if (cur < 0) cur = 0;
    cur += arr[i];
    dp[i + 1][0] = cur;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      dp[i][j] = dp[i - 1][j] + arr[i - 1];
      if (j > 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + arr[i - 1] + x);
      dp[i][j] = max(dp[i][j], 0);
    }
  }
  int ans = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) ans = max(ans, dp[j][i]);
    cout << ans << ' ';
  }
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
