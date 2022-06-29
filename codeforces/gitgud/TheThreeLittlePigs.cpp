#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

vector<ll> fact, ifact;

inline ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= x;
  return b % MOD;
}

inline ll inv(ll x) { return p(x, MOD - 2); }

inline ll nCr(ll n, ll r) { return n < r ? 0 : (fact[n] * ifact[r] % MOD) * ifact[n - r] % MOD; }

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  fact.resize(3 * n + 5); fact[0] = 1;
  for (int i = 1; i < 3 * n + 5; ++i) fact[i] = fact[i - 1] * i % MOD;
  ifact.resize(3 * n + 5); ifact[3 * n + 4] = inv(fact[3 * n + 4]);
  for (int i = 3 * n + 4; i > 0; --i) ifact[i - 1] = ifact[i] * i % MOD;
  vector<vector<int>> dp(3 * n + 1, vector<int>(3)); dp[0][0] = dp[0][1] = dp[0][2] = n;
  for (int i = 1; i <= 3 * n; ++i) {
    dp[i][0] = (((nCr(3 * n + 1, i + 1) - 2 * dp[i - 1][0] - dp[i - 1][1]) % MOD + MOD) % MOD) * 333333336 % MOD;
    dp[i][1] = (dp[i - 1][0] + dp[i][0]) % MOD;
    dp[i][2] = (dp[i - 1][1] + dp[i][1]) % MOD;
  }
  for (int i = 0; i < q; ++i) {
    int x; cin >> x;
    cout << dp[x][2] << '\n';
  }
  return 0;
}

