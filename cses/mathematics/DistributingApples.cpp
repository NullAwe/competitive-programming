#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

vector<ll> fact;

ll p(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = p(x, y >> 1);
  base = base * base % MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

ll inv(ll x) { return p(x, MOD - 2); }

ll nCr(int n, int r) { return (fact[n] * inv(fact[r]) % MOD) * inv(fact[n - r]) % MOD; }

int main() {
  int n, m; cin >> n >> m;
  fact.resize(n + m); fact[0] = 1;
  for (int i = 1; i < n + m; ++i) fact[i] = fact[i - 1] * i % MOD;
  cout << nCr(n + m - 1, m) << '\n';
  return 0;
}

