#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

int main() {
  int n, k; cin >> n >> k;
  string str; cin >> str;
  vector<ll> p(n + 1); p[0] = 1; for (int i = 1; i <= n; ++i) p[i] = p[i - 1] * 26 % MOD;
  vector<int> arr(n); for (int i = 0; i < n; ++i) arr[i] = str[i] - 'a';
  vector<vector<ll>> dp(n + 1, vector<ll>(k + 1));
  vector<vector<ll>> fakeDP(n + 1, vector<ll>(k + 1));
  dp[0][k] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) dp[i][j] = dp[i - 1][j] * (arr[i - 1] + 1) % MOD;
    for (int j = 0; j <= k; ++j) fakeDP[i][j] = dp[i - 1][j];
    ll base = 25 - arr[i - 1];
    if (base == 0) continue;
    for (int l = 0; l + (n - i + 1) <= k; ++l) dp[i][l] = (dp[i][l] + ((dp[i - 1][l + (n - i + 1)] - fakeDP[i - 1][l + (n - i + 1)] + MOD) % MOD) * base % MOD) % MOD;
    for (int j = 1; (n - i + 1) * (j + 1) <= k && i - j > 0; ++j) for (int l = 0; l + (n - i + 1) * (j + 1) <= k; ++l)
      dp[i][l] = (dp[i][l] + ((dp[i - j - 1][l + (n - i + 1) * (j + 1)] - fakeDP[i - j - 1][l + (n - i + 1) * (j + 1)] + MOD) % MOD) * base % MOD) % MOD;
  }
  cout << dp[n][0] << '\n';
  return 0;
}
