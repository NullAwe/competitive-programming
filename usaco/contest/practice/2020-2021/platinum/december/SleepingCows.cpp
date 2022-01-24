#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pi pair<int, int>

const int MOD = 1e9 + 7;

int main() {
  int n; cin >> n;
  pi info[2 * n];
  for (int i = 0; i < n; ++i) cin >> info[i].first;
  for (int i = n; i < 2 * n; ++i) cin >> info[i].first;
  for (int i = n; i < 2 * n; ++i) info[i].second = 1;
  sort(info, info + 2 * n);
  int dp[2 * n + 1][n + 1][2];
  for (int i = 0; i <= 2 * n; ++i) for (int j = 0; j <= n; ++j) dp[i][j][0] = dp[i][j][1] = 0;
  dp[2 * n][0][0] = 1;
  for (int i = 2 * n - 1; i >= 0; --i) {
    for (int j = 0; j <= n; ++j) {
      if (info[i].second == 0) {
        dp[i][j][0] = dp[i + 1][j][0];
        if (j < n) dp[i][j][0] = (int) ((dp[i][j][0] + (ll) dp[i + 1][j + 1][0] * (j + 1)) % MOD);
        if (j < n) dp[i][j][1] = (int) (((ll) dp[i + 1][j + 1][1] * (j + 1)) % MOD);
      } else {
        if (j > 0) dp[i][j][0] = dp[i + 1][j - 1][0];
        dp[i][j][1] = (dp[i + 1][j][0] + dp[i + 1][j][1]) % MOD;
        if (j > 0) dp[i][j][1] = (dp[i][j][1] + dp[i + 1][j - 1][1]) % MOD;
      }
    }
  }
  // Output:
  cout << (dp[0][0][0] + dp[0][0][1]) % MOD << endl;
  return 0;
}
