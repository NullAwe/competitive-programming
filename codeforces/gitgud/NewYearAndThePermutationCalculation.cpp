#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MOD = 998244353;

ll exp(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = exp(x, y / 2);
  base *= base;
  base %= MOD;
  if (y % 2 == 1) base *= x;
  return base % MOD;
}

ll modInverse(ll x) {
  return exp(x, MOD - 2);
}

int main() {
  int n; cin >> n;
  vector<ll> fact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = (fact[i - 1] * i) % MOD;
  ll ans = fact[n];
  for (int i = 1; i < n - 1; ++i) {
    ans += (((fact[n] * modInverse(fact[i] + fact[i - 1])) % MOD) * (n - i - 1)) % MOD;
    ans %= MOD;
  }
  // Output:
  cout << ans << endl;
  return 0;
}
