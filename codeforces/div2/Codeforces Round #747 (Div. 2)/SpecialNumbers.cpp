#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1000000007;

ll mp(ll x, ll y) {
  if (y == 0) return 1;
  ll base = mp(x, y / 2);
  base *= base;
  base %= MOD;
  if (y % 2 == 1) base *= x;
  return base % MOD;
}

void solve() {
  int n, k, exp = 0; cin >> n >> k;
  ll ans = 0;
  while (k > 0) {
    if (k % 2) ans = (ans + mp(n, exp)) % MOD;
    ++exp;
    k >>= 1;
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}