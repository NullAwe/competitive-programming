#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

ll p(ll x, ll y) {
  x %= MOD;
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD;
    y >>= 1;
  }
  return ans;
}

ll inv(ll x) {
  return p(x, MOD - 2);
}

vector<ll> fact, finv;

ll nCr(ll n, ll r) {
  return (fact[n] * finv[r] % MOD) * finv[n - r] % MOD;
}

void solve() {
  int n, k; cin >> n >> k;
  fact.resize(n + 1), finv.resize(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = fact[i  - 1] * i % MOD;
  finv[n] = inv(fact[n]);
  for (int i = n - 1; i >= 0; --i) finv[i] = finv[i + 1] * (i + 1) % MOD;
  ll ans = 0;
  if (k == 0) {
    cout << p(3, n) << '\n';
    return;
  }
  for (int groups = 1; groups <= k; ++groups) {
    ll base = nCr(k - 1, groups - 1);
    if (n - k < groups - 1) break;
    if (n - k >= groups) {
      ll ways = nCr(n - k - groups + groups, groups);
      ways = ways * p(3, n - k - groups) % MOD;
      ll l = p(3, k - groups);
      ans += base * ways % MOD * l % MOD, ans %= MOD;
    }
    ll ways = nCr(n - k - groups + 1 + groups - 1, groups - 1);
    ways = ways * p(3, n - k - groups + 1) % MOD;
    ll l = p(3, k - groups);
    ans += base * ways % MOD * l % MOD, ans %= MOD;
  }
  cout << ans << '\n';
}

int main() {
  solve();
  return 0;
}
