#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= x;
  return b % MOD;
}

ll inv(ll x) { return p(x, MOD - 2); }

vector<ll> fact, back;

ll nCr(int n, int r) { return fact[n] * inv(fact[r]) % MOD * inv(fact[n - r]) % MOD; }

ll nCr(int n) { return back[n] * inv(fact[n]) % MOD; }

int main() {
  ll n, k; cin >> n >> k;
  fact.resize(n + 2); fact[0] = 1;
  for (int i = 1; i < n + 2; ++i) fact[i] = fact[i - 1] * i % MOD;
  back.resize(n + 2); back[0] = 1;
  for (int i = 1; i < n + 2; ++i) back[i] = back[i - 1] * ((k + 2 - i) % MOD) % MOD;
  ll ans = 0;
  for (int i = 0; i <= n; ++i) ans = (ans + p(2, i) * nCr(n, i) % MOD * nCr(i + 1) % MOD) % MOD;
  cout << ans << '\n';
  return 0;
}