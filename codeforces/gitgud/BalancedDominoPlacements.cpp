#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;
const int MAX_N = 4000;

vector<ll> fact(MAX_N), inv(MAX_N);

ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= x;
  return b % MOD;
}

inline ll nCr(ll n, ll r) { return (fact[n] * inv[r] % MOD) * inv[n - r] % MOD; }

int main() {
  fact[0] = 1; for (int i = 1; i < MAX_N; ++i) fact[i] = fact[i - 1] * i % MOD;
  inv[MAX_N - 1] = p(fact[MAX_N - 1], MOD - 2); for (int i = MAX_N - 1; i > 0; --i) inv[i - 1] = inv[i] * i % MOD;
  int n, m, d; cin >> n >> m >> d;
  vector<bool> tr(n), tc(m);
  for (int i = 0; i < d; ++i) {
    int a, b, c, d; cin >> a >> b >> c >> d; --a, --b, --c, --d;
    tr[a] = tr[c] = 1, tc[b] = tc[d] = 1;
  }
  int rows = 0, cols = 0;
  for (bool b : tr) rows += 1 - b;
  for (bool b : tc) cols += 1 - b;
  vector<vector<ll>> dp(n + 1, vector<ll>(n / 2 + 1));
  dp[0][0] = dp[1][0] = 1;
  for (int i = 1; i < n; ++i) {
    dp[i + 1] = dp[i];
    if (tr[i] || tr[i - 1]) continue;
    for (int j = 1; j <= n / 2; ++j) dp[i + 1][j] = (dp[i + 1][j] + dp[i - 1][j - 1]) % MOD;
  }
  vector<ll> dpr(m / 2 + 1);
  for (int i = 0; i <= m / 2; ++i) {
    for (int placed = 0; placed + 2 * i <= cols && 2 * placed + i <= rows; ++placed) {
      ll ways = dp[n][placed];
      ll canc = nCr(rows - 2 * placed, i);
      ll wcol = fact[cols - 2 * i] * inv[cols - 2 * i - placed] % MOD;
      dpr[i] = (dpr[i] + (ways * canc % MOD) * wcol % MOD) % MOD;
    }
  }
  dp = vector<vector<ll>>(m + 1, vector<ll>(m / 2 + 1));
  dp[0][0] = dp[1][0] = 1;
  for (int i = 1; i < m; ++i) {
    dp[i + 1] = dp[i];
    if (tc[i] || tc[i - 1]) continue;
    for (int j = 1; j <= m / 2; ++j) dp[i + 1][j] = (dp[i + 1][j] + dp[i - 1][j - 1]) % MOD;
  }
  ll ans = 0; for (int i = 0; i <= m / 2; ++i) ans = (ans + (dp[m][i] * dpr[i] % MOD) * fact[i] % MOD) % MOD;
  cout << ans << '\n';
  return 0;
}
