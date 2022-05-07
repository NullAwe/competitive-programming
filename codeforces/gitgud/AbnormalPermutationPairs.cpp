#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, MOD; cin >> n >> MOD;
  vector<vector<int>> dp(n + 1, vector<int>(n * (n + 1)));
  int shift = n * (n + 1) / 2;
  for (int i = shift + 1; i < n * (n + 1); ++i) dp[1][i] = 1;
  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      for (int k = 0; k < i; ++k) {
        for (int l = 0; l < n * (n + 1); ++l) {
          int ind = l + j - k;
          if (ind < 0 || ind >= n * (n + 1)) continue;
          dp[i][l] = (dp[i][l] + dp[i - 1][ind]) % MOD;
        }
      }
    }
  }
  vector<int> dp2(n + 1);
  for (int i = 3; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      for (int k = j + 1; k < i; ++k) dp2[i] = (dp2[i] + dp[i - 1][shift + j - k]) % MOD;
      dp2[i] = (dp2[i] + dp2[i - 1]) % MOD;
    }
  }
  cout << dp2[n] << '\n';
  return 0;
}
