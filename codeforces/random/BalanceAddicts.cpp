#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;
const int MAX_N = 100001;

inline ll p(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD, y >>= 1;
  }
  return ans;
}

inline ll inv(ll x) {
  return p(x, MOD - 2);
}

ll _f[MAX_N], _i[MAX_N];

inline ll nCr(ll n, ll r) {
  if (r < 0 || r > n) return 0;
  return _f[n] * _i[r] % MOD * _i[n - r] % MOD;
}

ll _p[MAX_N];

inline ll sum(int a, int b, bool inc = true) {
  return _p[b + inc] - _p[a];
}

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  if (n == 1) {
    cout << 1 << '\n';
    return;
  }
  _p[0] = 0; for (int i = 0; i < n; ++i) _p[i + 1] = _p[i] + arr[i];
  int l = 0, r = n - 1;
  ll mult = 1;
  while (true) {
    while (l < r - 1) {
      if (sum(0, l) == sum(r, n - 1)) break;
      if (sum(0, l) < sum(r, n - 1)) ++l;
      else --r;
    }
    if (sum(0, l) == sum(r, n - 1)) {
      if (l == r) break;
      if (l == r - 1) {
        mult = mult * 2 % MOD;
        break;
      }
      int nl = l, nr = r;
      while (nl < n - 1 && arr[nl + 1] == 0) ++nl;
      while (nr > 0 && arr[nr - 1] == 0) --nr;
      if (nl >= nr) {
        if (nl == n - 1) mult = mult * p(2, n - 1) % MOD;
        else mult = mult * p(2, nl - l + 1) % MOD;
        break;
      } else {
        int zl = nl - l, zr = r - nr;
        ll sum = 0;
        for (int div = 0; div < min(zl, zr) + 2; ++div)
          sum = (sum + nCr(zl + 1, div) * nCr(zr + 1, div) % MOD) % MOD;
        mult = mult * sum % MOD;
        l = nl, r = nr;
      }
      ++l, --r;
    } else break;
  }
  cout << mult << '\n';
}

int main() {
  _f[0] = 1; for (int i = 1; i < MAX_N; ++i) _f[i] = _f[i - 1] * i % MOD;
  _i[MAX_N - 1] = inv(_f[MAX_N - 1]); for (int i = MAX_N - 1; i > 0; --i) _i[i - 1] = _i[i] * i % MOD;
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
