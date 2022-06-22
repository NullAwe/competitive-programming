#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

ll p(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = p(x, y >> 1);
  base = base * base % MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

ll inv(ll x) { return p(x, MOD - 2); }

int main() {
  string str; cin >> str;
  int n = str.size();
  vector<ll> fact(n + 1); fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
  vector<int> count(26); for (int i = 0; i < n; ++i) ++count[str[i] - 'a'];
  ll ans = fact[n];
  for (int num : count) ans = ans * inv(fact[num]) % MOD;
  cout << ans << '\n';
  return 0;
}
