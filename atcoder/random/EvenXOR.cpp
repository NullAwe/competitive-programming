#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

inline ll p(ll x, ll y) {
  if (y < 0) return 0;
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD, y >>= 1;
  }
  return ans;
}

inline ll inv(ll x) {
  return p(x, MOD - 2);
}

int main() {
  int n; cin >> n;
  vector<ll> dp(n + 5); dp[0] = 1;
  for (int i = 1; i <= n + 4; ++i) {
    ll odd = p(2, i - 2), avail = p(2, n);
    dp[i] = dp[i - 1] * (avail - odd + MOD) % MOD;
  }
  ll fact = 1, ans = 0;
  for (int i = 0; i <= n + 4; ++i) {
    ans = (ans + dp[i] * inv(fact) % MOD) % MOD;
    fact = fact * (i + 1) % MOD;
  }
  cout << ans << '\n';
  return 0;
}