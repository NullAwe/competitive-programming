#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

inline ll _p(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD; y >>= 1;
  }
  return ans;
}

inline ll _i(ll x) {
  return _p(x, MOD - 2);
}

int main() {
  int n; cin >> n;
  vector<int> len(n);
  vector<ll> exp(n);
  len[0] = exp[0] = 1;
  for (int i = 1; i < n; ++i) {
    int p; cin >> p; --p;
    len[i] = len[p] + 1;
    exp[i] = (exp[p] + _i(len[i])) % MOD;
  }
  ll ans = 0;
  for (ll num : exp) ans = (ans + num) % MOD;
  cout << ans << '\n';
  return 0;
}