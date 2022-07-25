#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<vector<int>> colors(n + 1);
  for (int i = 0; i < n; ++i) colors[arr[i]].push_back(i);
  if (n == 1) {
    cout << 0 << '\n';
    return;
  }
  int dp[n][n][2];
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) dp[i][j][0] = dp[i][j][1] = 0;
  for (int i = 0; i < n; ++i) {
    if (i) dp[i][i][0] = arr[i] != arr[i - 1];
    if (i < n - 1) dp[i][i][1] = arr[i] != arr[i + 1];
  }
  for (int len = 2; len < n; ++len) {
    for (int i = 0; i + len <= n; ++i) {
      int j = i + len - 1;
      if (i) {
        int lc = arr[i - 1];
        dp[i][j][0] = min(dp[i + 1][j][0] + (arr[i] != lc), dp[i][j - 1][1] + (arr[j] != lc));
        for (int ind : colors[lc]) if (i <= ind && ind < j) dp[i][j][0] = min(dp[i][j][0], dp[i][ind - 1][0] + dp[ind + 1][j][0]);
      }
      if (j < n - 1) {
        int rc = arr[j + 1];
        dp[i][j][1] = min(dp[i + 1][j][0] + (arr[i] != rc), dp[i][j - 1][1] + (arr[j] != rc));
        for (int ind : colors[rc]) if (i <= ind && ind < j) dp[i][j][1] = min(dp[i][j][1], dp[i][ind - 1][1] + dp[ind + 1][j][1]);
      }
    }
  }
  cout << min(dp[1][n - 1][0], dp[0][n - 2][1]) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

