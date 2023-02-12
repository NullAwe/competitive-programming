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

ll fact(ll n) {
  ll ans = 1;
  for (int i = 1; i <= n; ++i) ans = ans * i % MOD;
  return ans;
}

ll nCr(ll n, ll r) {
  return fact(n) * inv(fact(r)) % MOD * inv(fact(n - r)) % MOD;
}

int main() {
  int n; cin >> n;
  cout << p(2, n) * fact(n) % MOD * inv(n + 1) % MOD * nCr(2 * n, n) % MOD << '\n';
  return 0;
}