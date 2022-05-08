#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 998244353;

ll p(ll x, ll y) {
  if (y <= 0) return 1;
  ll base = p(x, y >> 1);
  base = base * base % MOD;
  if (y & 1) base *= x;
  return base % MOD;
}

inline ll inv(ll x) { return p(x, MOD - 2); }

inline ll _gcd(ll a, ll b) { return b == 0 ? a : _gcd(b, a % b); }

int main() {
  int n, m; cin >> n >> m;
  vector<ll> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  sort(arr.begin(), arr.end());
  vector<ll> prefix(n + 1); for (int i = 0; i < n; ++i) prefix[i + 1] = (prefix[i] + arr[i]) % MOD;
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b;
    int lo = -1, hi = n;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (arr[mid] < b) lo = mid;
      else hi = mid;
    }
    int safe = lo + 1, harm = n - safe;
    if (harm < a) {
      cout << "0\n";
      continue;
    }
    ll num = (harm + 1 - a) * prefix[safe] % MOD, dem = harm + 1;
    ll num2 = (harm - a) * (prefix[n] - prefix[safe] + MOD) % MOD, dem2 = max(harm, 1);
    ll sn = (num * dem2 % MOD + num2 * dem % MOD) % MOD, sd = dem * dem2 % MOD;
    cout << sn * inv(sd) % MOD << '\n';
  }
  return 0;
}
