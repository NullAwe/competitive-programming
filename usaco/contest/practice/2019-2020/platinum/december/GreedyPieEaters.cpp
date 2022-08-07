#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int main() {
  ifstream in("pieaters.in");
  ofstream out("pieaters.out");
  int n, m; in >> n >> m;
  vector<pair<pii, int>> cows(m);
  for (int i = 0; i < m; ++i) in >> cows[i].second >> cows[i].first.first >> cows[i].first.second;
  for (int i = 0; i < m; ++i) --cows[i].first.first, --cows[i].first.second;
  vector<vector<vector<int>>> pre(n, vector<vector<int>>(n, vector<int>(n)));
  for (int i = 0; i < m; ++i)
    for (int j = cows[i].first.first; j <= cows[i].first.second; ++j)
      pre[cows[i].first.first][cows[i].first.second][j] = cows[i].second;
  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i + len <= n; ++i) {
      int j = i + len - 1;
      for (int k = i; k <= j; ++k)
        pre[i][j][k] = max(pre[i][j][k], max(pre[i + 1][j][k], pre[i][j - 1][k]));
    }
  }
  vector<vector<int>> dp(n, vector<int>(n));
  for (int len = 1; len <= n; ++len) {
    for (int i = 0; i + len <= n; ++i) {
      int j = i + len - 1;
      for (int k = i; k < j; ++k) dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
      if (len == 1) {
        dp[i][j] = pre[i][j][i];
        continue;
      }
      dp[i][j] = max(dp[i][j], pre[i][j][i] + dp[i + 1][j]);
      for (int k = i + 1; k < j; ++k) dp[i][j] = max(dp[i][j], pre[i][j][k] + dp[i][k - 1] + dp[k + 1][j]);
      dp[i][j] = max(dp[i][j], pre[i][j][j] + dp[i][j - 1]);
    }
  }
  out << dp[0][n - 1] << '\n';
  return 0;
}
