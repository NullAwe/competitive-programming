#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

inline ll p(ll x, ll y) {
  ll ans = 1;
  while (y > 0) {
    if (y & 1) ans = ans * x % MOD;
    x = x * x % MOD;
    y >>= 1;
  }
  return ans;
}

inline ll inv(ll x) { return p(x, MOD - 2); }

inline ll nCr(ll n, ll r, vector<ll>& fact) { return (fact[n] * inv(fact[r]) % MOD) * inv(fact[n - r]) % MOD; }

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, k; cin >> n >> k;
  if (k == 1) {
    cout << 0 << '\n';
    return 0;
  }
  vector<ll> fact(n + 1); fact[0] = 1; for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int same = 0; for (int i = 0; i < n; ++i) if (arr[i] == arr[(i + 1) % n]) ++same;
  ll ans = 0;
  for (int wrong = 0; wrong < n - same; ++wrong) {
    ll add = p(k - 2, wrong) * nCr(n - same, wrong, fact) % MOD;
    int rem = n - same - wrong;
    ll sum = p(2, rem - 1); if ((rem & 1) == 0) sum -= nCr(rem, rem >> 1, fact) * inv(2) % MOD;
    ans = (ans + add * ((sum + MOD) % MOD) % MOD) % MOD;
  }
  cout << ans * p(k, same) % MOD << '\n';
  return 0;
}
