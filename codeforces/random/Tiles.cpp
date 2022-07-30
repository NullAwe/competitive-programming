#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;
const int MAX_N = 3e5;

ll p(ll x, ll y) {
  if (!y) return 1;
  ll b = p(x, y >> 1);
  b = b * b % MOD;
  if (y & 1) b *= x;
  return b % MOD;
}

void fft(vector<int>& a, bool invert) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    int wlen = p(3, 952);
    if (invert) wlen = p(wlen, MOD - 2);
    for (int i = len; i < (1 << 20); i <<= 1) wlen = (ll) wlen * wlen % MOD;
    for (int i = 0; i < n; i += len) {
      int w = 1;
      for (int j = 0; j < len / 2; ++j) {
        int u = a[i + j], v = (ll) a[i + j + len / 2] * w % MOD;
        a[i + j] = (u + v) % MOD;
        a[i + j + len / 2] = (u - v + MOD) % MOD;
        w = (ll) w * wlen % MOD;
      }
    }
  }
  if (invert) {
    int n1 = p(n, MOD - 2);
    for (int i = 0; i < n; ++i) a[i] = (ll) a[i] * n1 % MOD;
  }
}

vector<int> multiply(vector<int>& a, vector<int>& b) {
  vector<int> fa = a, fb = b;
  int n = 1; while (n < a.size() + b.size()) n <<= 1;
  fa.resize(n), fb.resize(n);
  fft(fa, false), fft(fb, false);
  for (int i = 0; i < n; i++) fa[i] = (ll) fa[i] * fb[i] % MOD;
  fft(fa, true);
  return fa;
}

vector<ll> fact(MAX_N), inv(MAX_N);

inline ll nCr(ll n, ll r) { return r < 0 || r > n ? 0 : (fact[n] * inv[r] % MOD) * inv[n - r] % MOD; }

int main() {
  fact[0] = 1; for (int i = 1; i < MAX_N; ++i) fact[i] = fact[i - 1] * i % MOD;
  inv[MAX_N - 1] = p(fact[MAX_N - 1], MOD - 2); for (int i = MAX_N - 1; i > 0; --i) inv[i - 1] = inv[i] * i % MOD;
  int n; cin >> n;
  vector<int> dp(1, 1);
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    vector<int> mult(2 * dp.size() + a - b);
    for (int i = 0; i < mult.size(); ++i) mult[i] = nCr(a + b, b + i - dp.size());
    vector<int> ndp = multiply(dp, mult);
    dp = vector<int>(ndp.begin() + dp.size(), ndp.begin() + 2 * dp.size() + a - b);
  }
  int ans = 0;
  for (int num : dp) ans = (ans + num) % MOD;
  cout << ans << '\n';
  return 0;
}

