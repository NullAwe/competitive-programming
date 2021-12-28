#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

vector<ll> fact;

ll p(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = p(x, y / 2);
  base = (base * base) % MOD;
  if (y % 2 == 1) base *= x;
  return base % MOD;
}

ll inv(ll x) { return p(x, MOD - 2); }

ll nCr(ll n, ll r) {
  if (r < 0 || r > n) return 0;
  return (fact[n] * inv(fact[r]) % MOD) * inv(fact[n - r]) % MOD;
}

void solve() {
  int n, k; cin >> n >> k;
  fact = vector<ll>(n + 1); fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
  string str; cin >> str;
  ll ans = 0;
  if (k == 0) {
    cout << 1 << endl;
    return;
  }
  bool started = false;
  for (int i = 0; i < n; ++i) {
    if (str[i] == '0') continue;
    int ones = 0, li = i;
    for (int j = i; j < n; ++j) {
      if (str[j] == '1' && ones == k) break;
      if (str[j] == '1') ++ones;
      li = j;
    }
    if (ones < k) break;
    int fi = i;
    for (int j = i - 1; j >= 0; --j) {
      if (str[j] == '1') break;
      fi = j;
    }
    ll chooseFrom = li - fi;
    if (li == n - 1) ++chooseFrom;
    if (chooseFrom >= ones && ones >= 0) started = true;
    ans = (ans + nCr(chooseFrom, ones)) % MOD;
    if (li < n - 1) {
      for (int j = 1; j <= i - fi; ++j) {
        int before = j, after = ones - j - 1;
        if (after < 0 || after > li - i) break;
        if ((i - fi >= before && before >= 0) || (li - i >= after && after >= 0)) started = true;
        ans = (ans + nCr(i - fi, before) * nCr(li - i, after) % MOD) % MOD;
      }
    }
  }
  if (!started) ans = 1;
  // Output:
  cout << ans << endl;
}

int main() {
  solve();
  return 0;
}
