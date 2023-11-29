#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

inline ll p(ll x, ll y) {
  x %= MOD;
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD;
    y >>= 1;
  }
  return ans;
}

inline ll inv(ll x) {
  return p(x, MOD - 2);
}

int main() {
  int n, m; cin >> n >> m;
  vector<vector<ll>> dp(m + 1, vector<ll>(m + 1));
  for (int i = 0; i < m; ++i) dp[i][m] = m - i;
  ll i2 = inv(2);
  for (int j = m - 1; j > 0; --j) for (int i = j - 1; i >= 0; --i)
    dp[i][j] = (i2 * (dp[i + 1][j] + 1) % MOD + i2 * dp[i][j + 1] % MOD) % MOD;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n; ++i) --arr[i];
  arr.push_back(m);
  ll ans = 0;
  for (int i = 0; i < n; ++i) ans = (ans + dp[arr[i]][arr[i + 1]]) % MOD;
  cout << ans << '\n';
  return 0;
}
