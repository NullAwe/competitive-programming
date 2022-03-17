#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;
const int MAX_X = 200001;
const int SZ = 2 * MAX_X;

ll p(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = p(x, y >> 1);
  base = base * base % MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

ll inv(ll x) {
  return p(x, MOD - 2);
}

void modify(vector<ll>& t, int n, int p, ll v) {
  for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = (t[p] + t[p ^ 1]) % MOD;
}

ll query(vector<ll>& t, int n, int l, int r) {
  ll ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
    ans %= MOD;
  }
  return ans;
}

int main() {
  int n, m; cin >> n >> m;
  vector<int> s(n); for (int i = 0; i < n; ++i) cin >> s[i];
  vector<int> s2(m); for (int i = 0; i < m; ++i) cin >> s2[i];
  vector<int> count(MAX_X); for (int num : s) ++count[num];
  vector<ll> fact(MAX_X); fact[0] = 1; for (int i = 1; i < MAX_X; ++i) fact[i] = fact[i - 1] * i % MOD;
  ll base = fact[n]; for (int i = 1; i < MAX_X; ++i) base = base * inv(fact[count[i]]) % MOD;
  vector<ll> t(SZ);
  for (int i = 1; i < MAX_X; ++i) if (count[i]) modify(t, MAX_X, i, count[i]);
  ll ans = 0;
  for (int i = 0; i < min(n, m); ++i) {
    base = base * inv(n - i) % MOD;
    if (i == n - 1 && n < m && count[s2[i]]) {
      ++ans;
      break;
    }
    ans += base * query(t, MAX_X, 0, s2[i]) % MOD;
    ans %= MOD;
    if (!count[s2[i]]) break;
    --count[s2[i]];
    modify(t, MAX_X, s2[i], count[s2[i]]);
    base = base * (count[s2[i]] + 1) % MOD;
  }
  cout << ans % MOD << '\n';
  return 0;
}
