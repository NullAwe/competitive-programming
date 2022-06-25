#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;
const int MAX_N = 4e5 + 1;

vector<ll> fact(MAX_N);

ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= x;
  return b % MOD;
}

ll inv(ll x) { return p(x, MOD - 2); }

ll nCr(ll n, ll r) { return (fact[n] * inv(fact[r]) % MOD) * inv(fact[n - r]) % MOD; }

void solve() {
  int n; cin >> n;
  fact[0] = 1; for (int i = 1; i < MAX_N; ++i) fact[i] = fact[i - 1] * i % MOD;
  ll ans = 0;
  for (int i = 0; i < n + 1; ++i) {
    int x; cin >> x;
    if (!x) continue;
    ans = (ans + nCr(x + i, i + 1)) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  solve();
  return 0;
}
