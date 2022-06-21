#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;
const int MAX_N = 1e6 + 1;

vector<ll> fact(MAX_N);

ll p(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = p(x, y >> 1);
  base *= base;
  base %= MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

ll inv(int x) { return p(x, MOD - 2); }

ll nCr(int n, int r) { return (fact[n] * inv(fact[r]) % MOD) * inv(fact[n - r]) % MOD; }

int main() {
  int n; cin >> n;
  fact[0] = 1; for (int i = 1; i < MAX_N; ++i) fact[i] = fact[i - 1] * i % MOD;
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    cout << nCr(a, b) << '\n';
  }
  return 0;
}

