#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, MOD; cin >> n >> MOD;
  int nCr[n + 1][n + 1];
  for (int i = 0; i <= n; ++i) nCr[i][i] = nCr[i][0] = 1;
  for (int i = 2; i <= n; ++i) for (int j = 1; j < i; ++j) nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % MOD;
  __int128 dp[n][3][n + 1];
  for (int i = 0; i < n; ++i) for (int sr = 0; sr < 3; ++sr) for (int j = 0; j <= n; ++j) dp[i][sr][j] = 0;
  for (int sr = 0; sr < 3; ++sr) dp[0][sr][0] = 1, dp[1][sr][1] = 1;
  dp[1][0][0] = 1, dp[1][0][1] = 0;
  for (int i = 2; i < n; ++i) {
    for (int sr = 0; sr < 3; ++sr) {
      for (int j = i / 2; j <= i; ++j) {
        for (int k = 0; k < i; ++k) {
          int a = k, b = i - k - 1;
          for (int ml = max(a / 2, j - b - 1); ml <= min(j - b / 2 - 1, a); ++ml)
            dp[i][sr][j] = dp[i][sr][j] + dp[a][sr & 2][ml] * dp[b][sr & 1][j - ml - 1] * nCr[j - 1][ml];
        }
        dp[i][sr][j] %= MOD;
      }
    }
  }
  int ans = 0;
  for (int j = n / 2; j <= n; ++j) {
    for (int k = 0; k < n; ++k) {
      int a = k, b = n - k - 1;
      for (int ml = max(a / 2, j - b - 1); ml <= min(j - b / 2 - 1, a); ++ml)
        ans = (ans + ((long long) dp[a][2][ml] * dp[b][1][j - ml - 1] % MOD) * nCr[j - 1][ml] % MOD) % MOD;
    }
  }
  cout << ans << '\n';
  return 0;
}
